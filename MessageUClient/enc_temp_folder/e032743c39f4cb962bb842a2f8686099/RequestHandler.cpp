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


namespace fs = std::filesystem;

RequestHandler::RequestHandler(const Connection& conn,  CurrentClient& currentClient, UImanager& uiManager) : conn(conn), currentClient(currentClient), uiManager(uiManager) {
}


RequestHandler::~RequestHandler(){
}


bool RequestHandler::handleChoice(const int choice)
{
	std::string binaryData = "";
	try {
		switch (static_cast<MenuOption> (choice)) {
		case MenuOption::REGISTER:
			binaryData = RequestHandler::getRegisterClientBinaryRequest();
			break;
		case MenuOption::GET_CLIENT_LIST:
			binaryData = RequestHandler::getClientsListBinaryRequest();
			break;
		case MenuOption::GET_PUBLIC_KEY:
			binaryData = RequestHandler::getPublicKeyBinaryRequest();
			std::cout << "Request for public key\n";
			break;
		case MenuOption::GET_WAITING_MESSAGES:
			std::cout << "Request for waiting messages\n";
			break;
		case MenuOption::SEND_TEXT_MESSAGE:
			std::cout << "Send a text message\n";
			break;
		case MenuOption::GET_SYMMETRIC_KEY:
			std::cout << "Send a request for symmetric key\n";
			break;
		case MenuOption::SEND_SYMMETRIC_KEY:
			std::cout << "Send your symmetric key\n";
			break;
		case MenuOption::SEND_FILE:
			std::cout << "Send a file\n";
			break;

		default:
			break;
		}
		sendBinaryData(binaryData);
		return true;
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


std::string RequestHandler::getRegisterClientBinaryRequest()
{
	try {
		if (std::filesystem::exists(ME_INFO)) {
			throw std::runtime_error("Error: user info file already exists");
		}
		std::string userName = uiManager.getUserNameFromConsole(); // checks if length is valid	
		currentClient.setUserName(userName);
		std::string publicKey = currentClient.getPublicKey();
		uint32_t payloadSize = REGISTER_REQUEST_PAYLOAD_SIZE;
		RegisterRequest registerReq = RegisterRequest(userName, publicKey, payloadSize);
		std::string binaryData = registerReq.getBinary();
		return binaryData;			
	}
	catch (const std::exception& e) {
		throw e;
	}
}

std::string RequestHandler::getClientsListBinaryRequest()
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

std::string RequestHandler::getPublicKeyBinaryRequest()
{
	try {
		BaseRequest request = BaseRequest(static_cast<uint16_t>(RequestCode::GET_PUBLIC_KEY), currentClient.getClientId());
		std::string binaryData = request.getBinaryHeader();
		std::string requestedUserName = uiManager.getUserNameFromConsole();
		std::string requestedClientId = currentClient.getClientIdByName(requestedUserName);
		binaryData.append(requestedClientId);
		return binaryData;
	}
	catch (const std::exception& e) {
		throw e;
	}

}

void RequestHandler::requestWaitingMessages()
{
}

void RequestHandler::sendTextMessage()
{
}

void RequestHandler::requestSymmetricKey()
{
}

void RequestHandler::sendSymmetricKey()
{
}






void RequestHandler::sendBinaryData(std::string& binaryData) {
	int sendRes = send(conn.getClientSocket(), binaryData.c_str(), static_cast<int>(binaryData.size()), 0);

	if (sendRes == SOCKET_ERROR) {
		throw std::runtime_error("Error: send failed");
	}
	std::cout << "DEBUG in RequestHandler sendBinaryData sendRes: " << sendRes << std::endl; //DEBUG	

}

