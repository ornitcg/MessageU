#pragma once
#include "Client.h"



class CurrentClient : public Client
{
private:
	std::vector<std::pair<std::string, Client>> clientList ;
	std::map<std::string, std::string> symmetricKeys; //client id, symmetric key


public:

	CurrentClient();
	~CurrentClient();


	void loadFromFile();
	void saveToFile() ;
	void generateNewKeys();

	void setClientsList(std::vector<std::pair<std::string, Client>> clientList);
	void updateClientList(const std::vector<std::pair<std::string, Client>>& newClientList);
	std::string getClientIdByName(const std::string& name) const;
	const std::vector<std::pair<std::string, Client>>& getClientList() const;
	std::string getSymmetricKey(const std::string& clientId) const;


	// Methods for symmetric key management not implemented yet
	void addSymmetricKey(const std::string& clientId, const std::string& key);
	bool hasSymmetricKey(const std::string& clientId) const;

	void updateTargetPublicKey(const std::string& clientId, const std::string& publicKey);
};

