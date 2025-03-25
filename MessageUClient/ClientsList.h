#pragma once
#include "Client.h"
#include <vector>
#include <string>




class ClientsList
{
private:
	std::vector<std::pair<std::string, Client>> clientList  ;  //<userName, client>


public:
	ClientsList();
	~ClientsList();

	void updateClientList(const std::vector<std::pair<std::string, Client>>& newClientList);

	std::string getTargetClientIdByName(const std::string& userName) const;

	Client getTargetClientByUserName(std::string userName) const;

	void updateTargetPublicKey(const std::string& targetClientId, const std::string& targetPublicKey);

	bool hasSymmetricKey(const std::string& userName) const;

	bool hasPublicKey(const std::string& userName) const;

	std::string getSymmetricKey(const std::string& userName) const;

	void updateClientsList(std::vector<std::pair<std::string, Client>>& clientList);

	const std::vector<std::pair<std::string, Client>>& getClientList() const;

	void displayClientListNames();


};

