#include "ClientsList.h"

ClientsList::ClientsList()
{
}

ClientsList::~ClientsList()
{
}

//Adds to clients list, clients that their user name does not appear in it
void ClientsList::updateClientsListWithNewClients(const std::vector<std::pair<std::string, Client>>& newClientsList)
{
	for (auto client : newClientsList) {
		bool found = false;
		for (auto existingClient : clientsList) {
			if (client.first == existingClient.first) {
				found = true;
				break;
			}
		}
		if (!found) {
			clientsList.push_back(client);
		}
	}
}

//finds just the clientId
std::string ClientsList::getTargetClientIdByUserName(const std::string& userName) const
{
	for (auto client : clientsList) {
		if (client.first == userName) {
			return client.second.getClientId();
		}
	}
	throw std::runtime_error("Error: client not found");
}

std::string ClientsList::getUserNameByTargetClientId(const std::string& targetClientId) const
{
	for (auto client : clientsList) {
		if (client.second.getClientId() == targetClientId) {
			return client.first;
		}
	}
	throw std::runtime_error("Error: client not found");
}


//finds the Client object
Client ClientsList::getTargetClientByUserName(std::string userName) const
{
	for (auto client : clientsList) {
		if (client.first == userName) {
			return client.second;
		}
	}
	throw std::runtime_error("Error: client not found");
}


void ClientsList::updateTargetPublicKey(const std::string& targetClientId, const std::string& targetPublicKey)
{
	for (auto& client : clientsList) {
		Client& targetClient = client.second;
		if (targetClient.getClientId() == targetClientId) {
			targetClient.setPublicKey(targetPublicKey);
			std::cout << "Public key received for " << client.first << std::endl;
			break;
		}
	}
}


bool ClientsList::hasSymmetricKey(const std::string& userName) const
{
	if (getSymmetricKeyByUserName(userName).empty()) {
		return false;
	}
}


bool ClientsList::hasPublicKey(const std::string& userName) const
{
	for (auto client : clientsList) {
		if (client.first == userName) {
			Client targetClient = client.second;
			if (targetClient.getPublicKey().empty()) {
				return false;
			}
			else {
				return true;
			}
		}
	}
}

void ClientsList::setSymmetricKeyForUser(const std::string& userName, const std::string& symmetricKey)
{
	try {
		for (auto& client : clientsList) {
			if (client.first == userName) {
				client.second.setSymKey(symmetricKey);
				break;
			}
		}
		throw std::runtime_error("Error: client not found");
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	
}


std::string ClientsList::getSymmetricKeyByUserName(const std::string& userName) const
{
	//search client list , find with user name, what the sym key
	for (auto client : clientsList) {
		if (client.first == userName) {
			Client targetClient = client.second;
			std::string& symKey = targetClient.getSymKey();
			return symKey;
		}
	}
}

//adds only the new users to the list
void ClientsList::updateClientsList(std::vector<std::pair<std::string, Client>>& ReceivedClientsList)
{
	for (auto receivedClientRecord : ReceivedClientsList) {
		bool found = false;
		for (auto existingClientRecord : this->clientsList) {
			if (receivedClientRecord.first == existingClientRecord.first) {
				found = true;
				break;
			}
		}
		if (!found) {
			this->clientsList.push_back(receivedClientRecord);
		}
	}
}

const std::vector<std::pair<std::string, Client>>& ClientsList::getClientsList() const
{
	return clientsList;
}

//displays only names
void ClientsList::displayClientsListNames()
{
	if (clientsList.size() == 0) {
		std::cout << "No clients registered" << std::endl;
	}
	else {
		for (auto& client : clientsList) {
			std::cout << client.first << std::endl;
			//std::cout << client.second.toString() << std::endl; //TODO DEBUG REMOVE
		}
	}

}