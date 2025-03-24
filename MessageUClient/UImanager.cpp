#include <string>
#include <iostream>
#include "utils.h"
#include "UImanager.h"
#include "RequestInfo.h"



UImanager::UImanager()
{
}

UImanager::~UImanager()
{
}

void UImanager::displayMenu() {
	std::cout << "\n==== Menu: ====\n";
	for (const auto& option : requestInfoVector) {

		std::cout << static_cast<int>(option.first) << ") " << option.second.description << "\n";
	}
	std::cout << "? ";
}



int UImanager::getChoice()
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


std::string UImanager::getUserNameFromConsole()
{
	std::cout << "Enter User name: " << std::endl;
	std::string userName;
	std::cin.ignore(); // clean the buffer from any garbage
	std::getline(std::cin, userName);
	if (userName.size() > MAX_NAME_SIZE) {
		throw std::runtime_error("Error: user name is too long");
	}
	return userName;
}

std::string UImanager::getClientIdFromConsole()
{
	std::cout << "Enter Client ID: " << std::endl;
	std::string clientId;
	std::cin.ignore(); // clean the buffer from any garbage
	std::getline(std::cin, clientId);
	if (clientId.size() > CLIENT_ID_SIZE) {
		throw std::runtime_error("Error: client ID is too long");
	}
	return clientId;
}


std::string UImanager::getCurrentUserTextMessageFromConsole()
{
	std::cout << "Enter message: " << std::endl;
	std::string message;
	std::cin.ignore(); // clean the buffer from any garbage
	std::getline(std::cin, message);
	if (message.size() > MSG_SIZE) {
		throw std::runtime_error("Error: message is too long");
	}
	return message;
}