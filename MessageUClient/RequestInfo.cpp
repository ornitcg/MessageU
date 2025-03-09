#include "RequestInfo.h"

#include <iostream>


std::string getRequestDescription(MenuOption request) {
	for (const auto& pair : requestInfoVector) {
		if (pair.first == request) {
			return pair.second.description;
		}
	}
	throw std::runtime_error("Invalid request option");
}

//const RequestInfo& getRequestInfo(MenuOption option)
//{
//	// TODO: insert return statement here
//}

void displayMenu() {
	std::cout << "\n==== Menu: ====\n";
	for (const auto& option : requestInfoVector) {

		std::cout << static_cast<int>(option.first) << ") " << option.second.description << "\n";
	}
	std::cout << "? ";
}

bool isValidChoice(const int choice)
{
	for (const auto& pair : requestInfoVector) {
		if (pair.first == static_cast<MenuOption>(choice)) {
			return true;
		}
	}
	return false;
}

RequestCode getProtocolCode(MenuOption option)
{
	for (const auto& pair : requestInfoVector) {
		if (pair.first == option) {
			return pair.second.protocolCode;
		}
	}
	throw std::runtime_error("Invalid request option");
}

MessageType getMessageType(MenuOption option)
{	
	for (const auto& pair : requestInfoVector) {
		if (pair.first == option) {
			return pair.second.messageType;
		}
	}
	throw std::runtime_error("Invalid request option");
}