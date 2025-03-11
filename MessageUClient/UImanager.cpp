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
	std::cin >> userName;
	std::cout << "userName size: " << userName.size() << std::endl; //DEBUG
	if (userName.size() > MAX_NAME_SIZE) {
		throw std::runtime_error("Error: user name is too long");
	}
	return userName;
}