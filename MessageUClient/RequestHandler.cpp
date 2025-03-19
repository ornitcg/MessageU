#include "RequestHandler.h"
#include "utils.h"
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "RequestInfo.h"
#include "RegisterRequest.h"
#include "Client.h"
#include "UImanager.h"
#include "UserNameException.h"


namespace fs = std::filesystem;

RequestHandler::RequestHandler(Client& client, UImanager& uiManager) : client(client), uiManager(uiManager) {
}

RequestHandler::~RequestHandler(){
}


bool RequestHandler::handleChoice(const int choice)
{
	std::cout << "in handleChoice " << std::endl; // TODO DEBUG
	try {
		switch (static_cast<MenuOption> (choice)) {
		case MenuOption::REGISTER:
			RequestHandler::registerClient();
			break;
		case MenuOption::GET_CLIENT_LIST:
			std::cout << "Request for clients list\n";
			break;
		case MenuOption::GET_PUBLIC_KEY:
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


void RequestHandler::registerClient()
{
	try {
		if (std::filesystem::exists(ME_INFO)) {
			throw std::runtime_error("Error: user info file already exists");
		}
		std::string userName = uiManager.getUserNameFromConsole(); // checks if length is valid	
		client.setUserName(userName);
		std::string publicKey = client.getPublicKey();
		uint32_t payloadSize = REGISTER_REQUEST_PAYLOAD_SIZE;
		RegisterRequest registerReq = RegisterRequest(userName, publicKey, payloadSize);
		std::string binaryData = registerReq.getBinary();
		int sendRes = send(client.getConnection().getClientSocket(), binaryData.c_str(), static_cast<int>(binaryData.size()), 0);
		
		if (sendRes == SOCKET_ERROR) {
			throw std::runtime_error("Error: send failed");
		}
		std::cout << "DEBUG sendRes: " << sendRes << std::endl; //DEBUG		
	}
	catch (const std::exception& e) {
		throw e;
	}
}

void RequestHandler::requestClientsList()
{
}

void RequestHandler::requestPublicKey()
{
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




