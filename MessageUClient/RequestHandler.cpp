#include "RequestHandler.h"
#include "utils.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "RequestInfo.h"
#include "RegisterRequest.h"
#include "Client.h"
#include "CurrentClient.h"
#include "UImanager.h"
#include "UserNameException.h"
#include  "MessageSendRequest.h"
#include "ClientsList.h"
#include "ListRequest.h"
#include "Message.h"


namespace fs = std::filesystem;

RequestHandler::RequestHandler(const Connection& conn,  CurrentClient& currentClient, UImanager& uiManager, ClientsList& clientsList,  EncryptionManager& encMngr) : conn(conn), currentClient(currentClient), uiManager(uiManager) ,clientsList(clientsList), encMngr(encMngr){
}


RequestHandler::~RequestHandler(){
}


bool RequestHandler::handleChoice(const int choice)
{
	std::string binaryData = "";
	try {
		switch (static_cast<MenuOption> (choice)) {
		case MenuOption::REGISTER:
			binaryData = RequestHandler::registerClientBinaryRequest();
			break;
		case MenuOption::GET_CLIENT_LIST:
			binaryData = RequestHandler::clientsListBinaryRequest();
			break;
		case MenuOption::GET_PUBLIC_KEY:
			binaryData = RequestHandler::publicKeyBinaryRequest();
			break;
		case MenuOption::GET_WAITING_MESSAGES:
			binaryData = RequestHandler::WaitingMessagesBinaryRequest();
			break;
		case MenuOption::SEND_TEXT_MESSAGE:
			binaryData = RequestHandler::sendTextMessageBinaryRequest();
			break;
		case MenuOption::GET_SYMMETRIC_KEY:
			binaryData = RequestHandler::symmetricKeyBinaryRequest();
			break;
		case MenuOption::SEND_SYMMETRIC_KEY: 
			binaryData = RequestHandler::sendSymmetricKeyBinaryRequest();
			break;
		case MenuOption::SEND_FILE:
			binaryData = RequestHandler::sendSendAFileBinaryRequest();
			break;

		default:
			break;
		}
		if (!binaryData.empty()) {
			sendBinaryData(binaryData);
			return true;
		}
		return false;
	}
	catch (const UserNameException& e) {
		std::cout << e.what() << std::endl;
		throw e;		
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	}
}

//returns binary data of a register request, ready to be sent
std::string RequestHandler::registerClientBinaryRequest()
{
	try {
		if (std::filesystem::exists(ME_INFO)) {
			throw std::runtime_error("Error: You are already registered");
		}

		std::string userName = uiManager.getUserNameFromConsole(); // checks if length is valid	
		currentClient.setUserName(userName);	

		uint32_t payloadSize = REGISTER_REQUEST_PAYLOAD_SIZE;
		std::string clientId = currentClient.getClientId();
		if (clientId.empty())
			clientId = std::string(CLIENT_ID_SIZE, '\0');
		RegisterRequest registerReq = RegisterRequest(clientId, userName, currentClient.getPublicKey(), payloadSize);
		std::string binaryData = registerReq.getBinary();
		return binaryData;			
	}
	catch (const std::exception& e) {
		throw e;
	}
}


//returns binary data of a clients-list request, ready to be sent
std::string RequestHandler::clientsListBinaryRequest()
{
	try {
		if (currentClient.getClientId().empty()) {
			throw std::runtime_error("Error: You have to register first!");
		}
		ListRequest request = ListRequest(currentClient.getClientId());
		std::string binaryData = request.getBinaryHeader();
		return binaryData;
	}
	catch (const std::exception& e) {
		throw e;
	}
}


//returns binary data of a public key request, ready to be sent
std::string RequestHandler::publicKeyBinaryRequest()
{
	try {
		BaseRequest request = BaseRequest( currentClient.getClientId() , static_cast<uint16_t>(RequestCode::GET_PUBLIC_KEY), CLIENT_ID_SIZE);
		request.setClientId(currentClient.getClientId());
		std::string binaryData = request.getBinaryHeader();
		std::string requestedUserName = uiManager.getUserNameFromConsole();
		std::string payload = clientsList.getTargetClientIdByUserName(requestedUserName);
		binaryData.append(payload);
		return binaryData;
	}
	catch (const std::exception& e) {
		throw e;
	}

}



//returns binary data of a waiting-messages request, ready to be sent
std::string RequestHandler::WaitingMessagesBinaryRequest() 
{
	try {		
		BaseRequest request = BaseRequest(currentClient.getClientId(), static_cast<uint16_t>(RequestCode::GET_WAITING_MESSAGES), NO_PAYLOAD);
		std::string binaryData = request.getBinaryHeader();
		return binaryData;
	}
	catch (const std::exception& e) {
		throw e;	
	}	
}



std::string RequestHandler::sendTextMessageBinaryRequest()
{
	try {
		uint16_t requestCode = static_cast<uint16_t>(RequestCode::SEND_MESSAGE);
		uint8_t messageType = static_cast<uint8_t>(MessageType::SEND_TEXT_MESSAGE);
		std::string targetUserName = uiManager.getUserNameFromConsole();
		std::string symKey = clientsList.getSymmetricKeyByUserName(targetUserName); //throws error if no sym key found		
		std::string textMessage = uiManager.getTextMessageFromConsole(); 		
		Client targetClient = clientsList.getClientObjectByUserName(targetUserName);
		std::string content = encMngr.encryptWithSymmetricKey(symKey, textMessage);
		return packBinaryForSend(currentClient.getClientId(), targetClient.getClientId(), messageType, content);		
	}
	catch (const std::exception& e) {
		throw e;
	}
}


//returns binary data of a get-symmetric-key request, ready to be sent
std::string RequestHandler::symmetricKeyBinaryRequest()
{
	try {
		uint8_t messageType = static_cast<uint8_t>(MessageType::GET_SYM_KEY);
		std::string targetUserName = uiManager.getUserNameFromConsole();
		if (!clientsList.hasPublicKey(targetUserName)) {
			throw std::runtime_error("Error: Request for user's public key first");
		}
		Client targetClient = clientsList.getClientObjectByUserName(targetUserName);
		targetClient.setSymKeyRequested(true);
		std::string content = EMPTY_CONTENT;
		return packBinaryForSend(currentClient.getClientId(), targetClient.getClientId(), messageType, content);
	}
	catch (const std::exception& e) {
		throw e;
	}
}


//returns binary data of a send-symmetric-key request, ready to be sent
std::string RequestHandler::sendSymmetricKeyBinaryRequest()
{
	try {
		uint8_t messageType = static_cast<uint8_t>(MessageType::SEND_SYM_KEY);
		std::string targetUserName = uiManager.getUserNameFromConsole();
		Client targetClient = clientsList.getClientObjectByUserName(targetUserName);
		if (!targetClient.wasSymKeyRequested()) {
			throw std::runtime_error("Error: Symmetric key will be sent only by request");
		}
		std::string targetPublicKey = targetClient.getPublicKey();
		std::string plainContent = ensureSymKeyforTargetClient(targetClient);		
		std::string currentClientId = currentClient.getClientId();
		std::string content = encMngr.encryptWithTargetPublicKey(targetPublicKey, plainContent);
		return packBinaryForSend(currentClient.getClientId(), targetClient.getClientId(), messageType, content);		
	}
	catch (const std::exception& e) {
		throw e;
	}	
}

std::string RequestHandler::sendSendAFileBinaryRequest() {
	std::string binaryData;
	try {
		uint8_t messageType = static_cast<uint8_t>(MessageType::SEND_FILE);
		std::string targetUserName = uiManager.getUserNameFromConsole();
		Client targetClient = clientsList.getClientObjectByUserName(targetUserName);
		std::string symkey = targetClient.getSymKey();		
		std::string filePath = uiManager.getFilePathFromConsole(); 
		std::string binaryfileData = readFileData(filePath);
		std::string content = encMngr.encryptWithSymmetricKey(symkey, binaryfileData);
		return packBinaryForSend(currentClient.getClientId(), targetClient.getClientId(), messageType, content );
	}
	catch (const std::exception& e) {
		throw e;
	}
}

std::string RequestHandler::packBinaryForSend(std::string& senderclientId, std::string& targetClientId, uint8_t& messageType, std::string& content) {
	Message message = Message(targetClientId, messageType, content);
	uint32_t payloadSize = SEND_MESSAGE_HEADER_SIZE + static_cast<uint32_t>(content.size());
	MessageSendRequest request = MessageSendRequest(senderclientId, static_cast<uint16_t>(RequestCode::SEND_MESSAGE), payloadSize, message);
	return request.getBinary();
}



std::string RequestHandler::ensureSymKeyforTargetClient(Client& targetClient) { 
	std::string symKey;
	try {
		symKey = targetClient.getSymKey();
	}
	catch (...) {
		symKey = encMngr.generateSymmetricKey();
		targetClient.setSymKey(symKey);
	}		
	return targetClient.getSymKey();
}




/* performs the actual send */
void RequestHandler::sendBinaryData(std::string& binaryData) {
	uint32_t bytesToSend = static_cast<uint32_t>(binaryData.size());
	uint32_t bytesSent = 0;
	int sendRes = 0;
	while (true)
	{
		sendRes = send(conn.getClientSocket(), binaryData.c_str() + bytesSent, min(MAX_BUFF, bytesToSend - bytesSent), 0);
		if (sendRes == SOCKET_ERROR) {
			throw std::runtime_error("Error: send failed");
		}
		bytesSent += sendRes;
		if (bytesSent == bytesToSend) {
			break;
		}
	}

	//int sendRes = send(conn.getClientSocket(), binaryData.c_str(), static_cast<int>(binaryData.size()), 0); //REMOVE
	/*if (sendRes == SOCKET_ERROR) {
		throw std::runtime_error("Error: send failed");
	}*/
}





