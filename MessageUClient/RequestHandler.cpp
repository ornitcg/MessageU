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
			std::cout << "Send a file\n";
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
std::string RequestHandler::WaitingMessagesBinaryRequest() //604
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
		/*if (!clientsList.hasSymmetricKey(targetUserName)) {
			throw std::runtime_error("Error: Request for symmetric key, from this user, first");
		}*/
		std::string textMessage = uiManager.getTextMessageFromConsole(); 
		Client targetClient = clientsList.getTargetClientObjectByUserName(targetUserName);
		std::string symKey = targetClient.getSymKey();		

		std::string encryptedMessage = encMngr.encryptWithSymmetricKey(symKey, textMessage);		
		uint32_t msgSize = static_cast<uint32_t>(encryptedMessage.size());
		// print text message
		std::cout << "Encrypted message: " << encryptedMessage << std::endl;
		uint32_t payloadSize = CLIENT_ID_SIZE + MESSAGE_TYPE_FIELD_SIZE + CONTENT_SIZE_FIELD_SIZE + msgSize;
		Message message = Message(targetClient.getClientId(), messageType, msgSize, encryptedMessage);
		MessageSendRequest request = MessageSendRequest(currentClient.getClientId(), requestCode, payloadSize, message);
		return request.getBinary();
	}
	catch (const std::exception& e) {
		throw e;
	}
}


//returns binary data of a get-symmetric-key request, ready to be sent
std::string RequestHandler::symmetricKeyBinaryRequest()
{
	try {
		uint16_t requestCode = static_cast<uint16_t>(RequestCode::SEND_MESSAGE);
		uint8_t messageType = static_cast<uint8_t>(MessageType::GET_SYM_KEY);
		std::string targetUserName = uiManager.getUserNameFromConsole();
		if (!clientsList.hasPublicKey(targetUserName)) {
			throw std::runtime_error("Request for public key , for this user, first");
		}
		Client targetClient = clientsList.getTargetClientObjectByUserName(targetUserName);
		uint32_t contentSize = 0;
		std::string content = EMPTY_CONTENT;
		uint32_t payloadSize = SEND_MESSAGE_HEADER_SIZE + contentSize;
		Message message = Message(targetClient.getClientId(), messageType, contentSize, content);
		MessageSendRequest request = MessageSendRequest(currentClient.getClientId(), requestCode, payloadSize, message);
		std::string binaryData = request.getBinary();
		return binaryData;
	}
	catch (const std::exception& e) {
		throw e;
	}
}


//returns binary data of a send-symmetric-key request, ready to be sent
std::string RequestHandler::sendSymmetricKeyBinaryRequest()
{
	try {
		uint16_t requestCode = static_cast<uint16_t>(RequestCode::SEND_MESSAGE);
		uint8_t messageType = static_cast<uint8_t>(MessageType::SEND_SYM_KEY);
		std::string targetUserName = uiManager.getUserNameFromConsole();
		Client targetClient = clientsList.getTargetClientObjectByUserName(targetUserName);
		std::string targetPublicKey = targetClient.getPublicKey();
		//std::string plainContent = getSymKeyforTargetClient(targetUserName);	
		std::string plainContent = "12345678910";

		std::string currentClientId = currentClient.getClientId();

		//std::string content = encMngr.encryptWithTargetPublicKey(targetPublicKey, plainContent);

		std::string content = plainContent;
		std::cout << "Encrypted symmetric key (hex): "; //REMOVE
		printAsHex(content);//REMOVE

		uint32_t contentSize = static_cast<uint32_t>(content.size());
		Message message = Message(targetClient.getClientId(), messageType, contentSize, content);

		uint32_t payloadSize = SEND_MESSAGE_HEADER_SIZE + contentSize;
		MessageSendRequest request = MessageSendRequest(currentClient.getClientId(), requestCode, payloadSize, message);
		return request.getBinary();
	}
	catch (const std::exception& e) {
		throw e;
	}
	
}

std::string RequestHandler::getSymKeyforTargetClient(std::string targetUserName) {
	std::string symKey = "";
	if (!clientsList.hasSymmetricKey(targetUserName)) {
		symKey = encMngr.generateSymmetricKey();
		
		clientsList.setSymmetricKeyForUser(targetUserName, symKey);
	}
	else {
		symKey = clientsList.getSymmetricKeyByUserName(targetUserName);
	}
	std::cout << "original symmetric key (hex): " << std::endl;//REMOVE
	printAsHex(symKey);//REMOVE
	return symKey;
}




//performs the actual send
void RequestHandler::sendBinaryData(std::string& binaryData) {
	int sendRes = send(conn.getClientSocket(), binaryData.c_str(), static_cast<int>(binaryData.size()), 0);

	if (sendRes == SOCKET_ERROR) {
		throw std::runtime_error("Error: send failed");
	}
}



