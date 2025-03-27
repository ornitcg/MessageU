#pragma once
#include "Client.h"



class CurrentClient : public Client
{
private:
	std::string privateKey = "";


public:

	CurrentClient();
	CurrentClient(std::pair < std::string, std::string> rsaKeys);
	~CurrentClient();

	void loadFromFile();

	void saveToFile(EncryptionManager& encMngr);

	void setRSAKeys(std::pair<std::string, std::string> rsaKeys);

	void setPrivateKey(std::string& privateKey);
	
	std::string& getPrivateKey();



};

