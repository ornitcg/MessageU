#pragma once
#include <string>
#include <vector>


#define GET_SYM_KEY_MSG "Request for symmetric key"
#define RECV_SYM_KEY_MSG "Symmetric key received"
#define ERROR_TEXT_MSG "Can't decrypt message"
#define UNKNOWN_USER "Unknown user"
#define MESSAGE_DISPLAY_ERROR "Can't decrypt message!"
#define DESTINATION_FILE_DIR_NAME "MessageUfiles"
#define MISSING_PUBLIC_KEY_MSG "Public key needed. Please request it first"
#define MISSING_SYM_KEY_MSG "Symmetric key needed. Please request it first"
#define FILE_NOT_FOUND_MSG "File not found"
#define CLIENT_NOT_FOUND_MSG "Client not found"



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
	std::string getFilePathFromConsole();
	std::string getCurrentUserTextMessageFromConsole();
	std::string getTextMessageFromConsole();
	void displaySingleMessage(std::string& userName, const std::string& content);
	void displaySingleMessage(const std::string& content);
	void displayClientsListNames(std::vector<std::string>& namesList);
};

