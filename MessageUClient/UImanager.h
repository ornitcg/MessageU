#pragma once
#include <string>


class UImanager
{




public:
	UImanager();
	~UImanager();
	void displayMenu();
	int getChoice();
	std::string getUserNameFromConsole();
};

