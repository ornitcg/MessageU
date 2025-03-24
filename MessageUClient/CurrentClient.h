#pragma once
#include "Client.h"



class CurrentClient : public Client
{
private:
	std::string privateKey = "";
	std::vector<std::pair<std::string, Client>> clientList;  //<userName, client>


public:

	CurrentClient();
	CurrentClient(std::pair < std::string, std::string> rsaKeys);
	~CurrentClient();

	void loadFromFile();

	void saveToFile(EncryptionManager& encMngr);

	void setClientsList(std::vector<std::pair<std::string, Client>> clientList);
	
	void updateClientList(const std::vector<std::pair<std::string, Client>>& newClientList);

	std::string getTargetClientIdByName(const std::string& userName) const;

	Client getTargetClientByUserName(std::string userName) const;

	void setRSAKeys(std::pair<std::string, std::string> rsaKeys);

	void setPrivateKey(std::string& privateKey);
	
	const std::vector<std::pair<std::string, Client>>& getClientList() const;

	std::string getSymmetricKey(const std::string& clientId) const;

	bool hasSymmetricKey(const std::string& clientId) const;

	void updateTargetPublicKey(const std::string& clientId, const std::string& publicKey);
};

