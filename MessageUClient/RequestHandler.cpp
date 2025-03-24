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
#include  "MessageRequest.h"


namespace fs = std::filesystem;

RequestHandler::RequestHandler(const Connection& conn,  CurrentClient& currentClient, UImanager& uiManager, EncryptionManager& encMngr) : conn(conn), currentClient(currentClient), uiManager(uiManager) , encMngr(encMngr){
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
			std::cout << "Request for waiting messages\n";
			break;
		case MenuOption::SEND_TEXT_MESSAGE:
			binaryData = RequestHandler::sendTextMessageBinaryRequest();
			std::cout << "Send a text message\n";
			break;
		case MenuOption::GET_SYMMETRIC_KEY:
			binaryData = RequestHandler::symmetricKeyBinaryRequest();
			std::cout << "Send a request for symmetric key\n"; //151 -603 TODO
			break;
		case MenuOption::SEND_SYMMETRIC_KEY: 
			//binaryData = RequestHandler::sendSymmetricKeyBinaryRequest();
			std::cout << "Send your symmetric key\n"; //152 - 603 TODO
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


std::string RequestHandler::registerClientBinaryRequest()
{
	try {
		if (std::filesystem::exists(ME_INFO)) {
			throw std::runtime_error("Error: user info file already exists");
		}

		std::string userName = uiManager.getUserNameFromConsole(); // checks if length is valid	
		currentClient.setUserName(userName);	

		uint32_t payloadSize = REGISTER_REQUEST_PAYLOAD_SIZE;
		RegisterRequest registerReq = RegisterRequest(userName, currentClient.getPublicKey(), payloadSize);
		std::string binaryData = registerReq.getBinary();
		return binaryData;			
	}
	catch (const std::exception& e) {
		throw e;
	}
}

std::string RequestHandler::clientsListBinaryRequest()
{
	try {
		BaseRequest request = BaseRequest(static_cast<uint16_t>(RequestCode::GET_CLIENT_LIST), currentClient.getClientId());
		std::string binaryData = request.getBinaryHeader();
		return binaryData;
	}
	catch (const std::exception& e) {
		throw e;
	}
}

std::string RequestHandler::publicKeyBinaryRequest()
{
	try {
		BaseRequest request = BaseRequest(static_cast<uint16_t>(RequestCode::GET_PUBLIC_KEY), CLIENT_ID_SIZE);
		request.setClientId(currentClient.getClientId());
		std::string binaryData = request.getBinaryHeader();
		std::string requestedUserName = uiManager.getUserNameFromConsole();
		std::string payload = currentClient.getTargetClientIdByName(requestedUserName);
		binaryData.append(payload);
		return binaryData;
	}
	catch (const std::exception& e) {
		throw e;
	}

}

std::string RequestHandler::WaitingMessagesBinaryRequest() //604
{
	try {
		BaseRequest request = BaseRequest(static_cast<uint16_t>(RequestCode::GET_WAITING_MESSAGES), currentClient.getClientId());
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
		uint8_t messageType = static_cast<uint8_t>(MessageType::SEND_TEXT_MESSAGE);
		std::string targetUserName = uiManager.getUserNameFromConsole();
		std::string messageToTargetUser = uiManager.getCurrentUserTextMessageFromConsole();
		Client targetClient = currentClient.getTargetClientByUserName(targetUserName);
		uint32_t contentSize = static_cast<uint32_t>(messageToTargetUser.size());
		MessageRequest request = MessageRequest(currentClient.getClientId(), targetClient.getClientId(), messageType, contentSize, messageToTargetUser);
		std::string binaryData = request.getBinary();
		return binaryData;
	}
	catch (const std::exception& e) {
		throw e;
	}
}



std::string RequestHandler::symmetricKeyBinaryRequest()
{
	try {
		uint8_t messageType = static_cast<uint8_t>(MessageType::GET_SYM_KEY);
		std::string targetUserName = uiManager.getUserNameFromConsole();
		Client targetClient = currentClient.getTargetClientByUserName(targetUserName);
		uint32_t contentSize = 0;
		MessageRequest request = MessageRequest(currentClient.getClientId(), targetClient.getClientId(), messageType, NO_CONTENT, EMPTY_CONTENT);
		std::string binaryData = request.getBinary();
		return binaryData;
	}
	catch (const std::exception& e) {
		throw e;
	}
}

//std::string RequestHandler::sendSymmetricKeyBinaryRequest()
//{
//	try{
//		std::string targetUserName = uiManager.getUserNameFromConsole();
//		uint8_t messageType = static_cast<uint8_t>(MessageType::SEND_SYM_KEY);
//		Client targetClient = currentClient.getTargetClientByUserName(targetUserName);
//		
//		std::string symKey = currentClient.getSymmetricKey(targetUserName);
//		uint32_t contentSize = SYM_KEY_SIZE;
//		MessageRequest request = MessageRequest( currentClient.getClientId(), targetClientId, messageType, 0, "");
//	
//		std::string binaryData = request.getBinaryHeader();
//		std::string payload = currentClient.getSymmetricKey();
//		binaryData.append(payload);
//		BaseRequest request = BaseRequest(static_cast<uint16_t>(RequestCode::SEND_MESSAGE), currentClient.getClientId());
//
//		return binaryData;
//	}
//	catch (const std::exception& e) {
//		throw e;
//	}
//
//}
//





void RequestHandler::sendBinaryData(std::string& binaryData) {
	int sendRes = send(conn.getClientSocket(), binaryData.c_str(), static_cast<int>(binaryData.size()), 0);

	if (sendRes == SOCKET_ERROR) {
		throw std::runtime_error("Error: send failed");
	}
	std::cout << "DEBUG in RequestHandler sendBinaryData sendRes: " << sendRes << std::endl; //DEBUG	

}



