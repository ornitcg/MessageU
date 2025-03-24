#pragma once
#include <string>

// menu options for the user interface
enum class MenuOption : int {
	REGISTER = 110,
	GET_CLIENT_LIST = 120,
	GET_PUBLIC_KEY = 130,
	GET_WAITING_MESSAGES = 140,
	SEND_TEXT_MESSAGE = 150,
	GET_SYMMETRIC_KEY = 151,
	SEND_SYMMETRIC_KEY = 152,
	SEND_FILE = 153,
	EXIT = 0
};


class UImanager
{




public:
	UImanager();
	~UImanager();
	void displayMenu();
	int getChoice();
	std::string getUserNameFromConsole();
	std::string getClientIdFromConsole();
	std::string getCurrentUserTextMessageFromConsole();
};

