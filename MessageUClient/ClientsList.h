#pragma once
#include "Client.h"
#include <vector>
#include <string>




class ClientsList
{
private:
	std::vector<std::pair<std::string, Client>> clientsList  ;  //<userName, client>


public:
	ClientsList();
	~ClientsList();

	void updateClientsListWithNewClients(const std::vector<std::pair<std::string, Client>>& newClientsList);

	std::string getTargetClientIdByUserName(const std::string& userName) const;

	std::string getUserNameByClientId(const std::string& targetClientId) const;

	Client getTargetClientObjectByUserName(std::string userName) const;

	void updateTargetPublicKey(const std::string& targetClientId, const std::string& targetPublicKey);

	bool hasSymmetricKey(const std::string& userName) const;

	bool hasPublicKey(const std::string& userName) const;

	void setSymmetricKeyForUser(const std::string& userName, const std::string& symmetricKey);

	std::string& getSymmetricKeyByUserName(const std::string& userName) const;

	void updateClientsList(std::vector<std::pair<std::string, Client>>& clientsList);

	const std::vector<std::pair<std::string, Client>>& getClientsList() const;

	void displayClientsListNames();


};

