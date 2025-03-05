#include "client.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>


Client::Client()
{
}

Client::~Client()
{
}

void Client::displayClientMenu() {	
	std::cout << "\nMessageU client at your service.\n";
	for (size_t i = 0; i < menuOptions.size(); i++) {
		if (menuOptions[i].first == 0) {
			std::cout << "0) " << menuOptions[i].second << "\n";
		}
		else {
			std::cout << (i + 1) << ") " << menuOptions[i].first
				<< " (" << menuOptions[i].second << ")\n";
		}
	}
	std::cout << "? ";
}

bool Client::isValidChoice(int choice)
{
	if (choice < 0)
		return false;
	for (const auto& option : menuOptions) {
		if (option.first == choice) {
			return true;
		}
	}
	return false;
}

int Client::getChoice()
{	
	int choice;	
	std::cin >> choice;
	if (std::cin.fail() || ! Client::isValidChoice(choice)) {
		std::cin.clear();
		throw std::runtime_error("Invalid choice");
	}
	return choice;
}

void Client::handleChoice(int choice)
{
	switch (choice) {
	case 110:
		std::cout << "Register\n";
		break;
	case 120:
		std::cout << "Request for clients list\n";
		break;
	case 130:
		std::cout << "Request for public key\n";
		break;
	case 140:
		std::cout << "Request for waiting messages\n";
		break;
	case 150:
		std::cout << "Send a text message\n";
		break;
	case 151:
		std::cout << "Send a request for symmetric key\n";
		break;
	case 152:
		std::cout << "Send your symmetric key\n";
		break;	
	default:		
		break;
	}
	

}

