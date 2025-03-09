#include "client.h"
#include "utils.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "RequestInfo.h"
#include "RegisterRequest.h"

namespace fs = std::filesystem;

Client::Client(SOCKET clientSocket)
{
	this->clientSocket = clientSocket;
}

Client::~Client()
{
}



int Client::getChoice()
{
	int choice;
	std::cin >> choice;
	if (std::cin.fail() || !isValidChoice(choice)) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		
		throw std::runtime_error("Invalid choice");
	}
	std::cin.clear();
	return choice;
}

void Client::handleChoice( const MenuOption choice)
{
	try {
		switch (choice) {
		case MenuOption::REGISTER:
			Client::registerClient();			
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
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

}

std::string Client::getUserNameFromConsole()
{
	std::cout << "Enter User name: " << std::endl;
	std::string userName;
	std::cin >> userName;
	std::cout << "userName size: " << userName.size() << std::endl; //DEBUG
	if (userName.size() > MAX_NAME_SIZE) {
		throw std::runtime_error("Error: user name is too long");
	}
	return userName;
}





void Client::registerClient()
{
	std::cout << "in registerClient\n"; //TODO REMOVE DEBUG
	try {
		if (std::filesystem::exists(ME_INFO)) {
			throw std::runtime_error("Error: user info file already exists");
		}

		std::string userName = Client::getUserNameFromConsole(); // checks if length is valid		
		RegisterRequest registerReq = RegisterRequest(userName);
		std::string binaryData = registerReq.getBinary();
		int sendRes = send(clientSocket, binaryData.c_str(), static_cast<int>(binaryData.size()), 0);
		std::cout << "sendRes: " << sendRes << std::endl; //DEBUG

		if (sendRes == SOCKET_ERROR) {
			throw std::runtime_error("Error: send failed");
		}
		std::cout << "sendRes: " << sendRes << std::endl; //DEBUG


		std::ofstream file(ME_INFO);
		if (!file.is_open()) {
			throw std::runtime_error("Error: user info file creation failed");
		}
		file << userName;

		file.close();
	}
	catch (const std::exception& e) {
		throw e;
	}
}

void Client::requestClientsList()
{
}

void Client::requestPublicKey()
{
}

void Client::requestWaitingMessages()
{
}

void Client::sendTextMessage()
{
}

void Client::requestSymmetricKey()
{
}

void Client::sendSymmetricKey()
{
}

