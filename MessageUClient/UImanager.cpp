#include <string>
#include <iostream>
#include "utils.h"
#include "UImanager.h"
#include "RequestInfo.h"
#include <vector>
#include <algorithm>
#include <filesystem>



UImanager::UImanager()
{
}

UImanager::~UImanager()
{
}

void UImanager::displayMenu() {
	std::cout << "\nMessageU client at your service:\n";
	for (const auto& option : requestInfoVector) {
		std::cout << static_cast<int>(option.first) << ") " << option.second.description << "\n";
	}
	std::cout << "? ";
}


//choice from menu
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

std::string UImanager::getFilePathFromConsole() {
	std::cout << "Enter full file Path: " << std::endl;
	std::string filePath;
	std::cin.ignore(); // clean the buffer from any garbage
	std::getline(std::cin, filePath);	
	//print path
	std::cout << "File path: " << filePath << std::endl;
	return filePath;
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

//TODO TEST THIS
std::string UImanager::getTextMessageFromConsole() {
	std::string message;
	std::string line;
	std::cout << "Enter your message:" << std::endl;

	std::cin.clear(); // Clear any error flags
	while (std::getline(std::cin, line)) {
		if (line.empty()) {
			break;
		}

		if (!message.empty()) {
			message += "\n"; // Add newline between lines, not after the last line
		}
		message += line;
	}
	return message;
}


void UImanager::displaySingleMessage(std::string& userName,  const std::string& content) {
	std::cout << "FROM: " << userName << std::endl;
	std::cout << "CONTENT:"  << std::endl;
	std::cout << content << std::endl;
	std::cout << "----<EOM>----" << std::endl;
	std::cout << std::endl;
}

void UImanager::displaySingleMessage(const std::string& content)
{
	std::cout << content << std::endl;	
	std::cout << std::endl;
}

void UImanager::displayClientsListNames(std::vector<std::string>& namesList)
{
	if (namesList.size() == 0) {
		std::cout << "No other clients are registered\n" << std::endl;
	}
	else {
		std::sort(namesList.begin(), namesList.end());
		std::cout << "----------" << std::endl;
		std::cout << "Clients list:" << std::endl;
		std::cout << "----------" << std::endl;
		for (const auto& name : namesList) {
			std::cout << name << std::endl;
		}
	}
}
