#pragma once
#include "Client.h"
#include <string>



class CurrentClient : public Client
{
private:
	std::string privateKey = "";
	int currentChoice = 0 ;

public:

	CurrentClient();
	CurrentClient(std::pair < std::string, std::string> rsaKeys);
	~CurrentClient();

	void loadFromFile();

	void saveToFile(EncryptionManager& encMngr);

	void setRSAKeys(std::pair<std::string, std::string> rsaKeys);

	void setPrivateKey(std::string& privateKey);
	
	std::string& getPrivateKey();

	void setCurrentChoice(int choice);
	void forgetChoice();


};

