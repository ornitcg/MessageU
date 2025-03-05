#pragma once
#include <vector>
#include <string>



class Client
{
private:
	const std::vector<std::pair<int, std::string>> menuOptions = {
		{110, "Register"},
		{120, "Request for clients list"},
		{130, "Request for public key"},
		{140, "Request for waiting messages"},
		{150, "Send a text message"},
		{151, "Send a request for symmetric key"},
		{152, "Send your symmetric key"},
		{0, "Exit client"}
	};

public:
	Client();
	~Client();
	void displayClientMenu();
	bool isValidChoice(int choice);
	int getChoice();
	void handleChoice(int choice);

};

