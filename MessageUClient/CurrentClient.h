#pragma once
#include "Client.h"



class CurrentClient : public Client
{
private:
	std::string privateKey = "";
	//std::vector<std::pair<std::string, Client>> clientList;  //<userName, client>


public:

	CurrentClient();
	CurrentClient(std::pair < std::string, std::string> rsaKeys);
	~CurrentClient();

	void loadFromFile();

	void saveToFile(EncryptionManager& encMngr);

	void setRSAKeys(std::pair<std::string, std::string> rsaKeys);

	void setPrivateKey(std::string& privateKey);
	



};

