#include "ClientsList.h"

ClientsList::ClientsList()
{
}

ClientsList::~ClientsList()
{
}

//Adds to clients list, clients that their user name does not appear in it
void ClientsList::updateClientList(const std::vector<std::pair<std::string, Client>>& newClientList)
{
	for (auto client : newClientList) {
		bool found = false;
		for (auto existingClient : clientList) {
			if (client.first == existingClient.first) {
				found = true;
				break;
			}
		}
		if (!found) {
			clientList.push_back(client);
		}
	}
}

//finds just the clientId
std::string ClientsList::getTargetClientIdByName(const std::string& userName) const
{
	for (auto client : clientList) {
		if (client.first == userName) {
			return client.second.getClientId();
		}
	}
	throw std::runtime_error("Error: client not found");
}


//finds the Client object
Client ClientsList::getTargetClientByUserName(std::string userName) const
{
	for (auto client : clientList) {
		if (client.first == userName) {
			return client.second;
		}
	}
	throw std::runtime_error("Error: client not found");
}


void ClientsList::updateTargetPublicKey(const std::string& targetClientId, const std::string& targetPublicKey)
{
	for (auto& client : clientList) {
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
	if (getSymmetricKey(userName).empty()) {
		return false;
	}
}


bool ClientsList::hasPublicKey(const std::string& userName) const
{
	for (auto client : clientList) {
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


std::string ClientsList::getSymmetricKey(const std::string& userName) const
{
	//search client list , find with user name, what the sym key
	for (auto client : clientList) {
		if (client.first == userName) {
			Client targetClient = client.second;
			std::string& symKey = targetClient.getSymKey();
			return symKey;
		}
	}
}

//adds only the new users to the list
void ClientsList::updateClientsList(std::vector<std::pair<std::string, Client>>& ReceivedClientList)
{
	for (auto receivedClientRecord : ReceivedClientList) {
		bool found = false;
		for (auto existingClientRecord : this->clientList) {
			if (receivedClientRecord.first == existingClientRecord.first) {
				found = true;
				break;
			}
		}
		if (!found) {
			this->clientList.push_back(receivedClientRecord);
		}
	}
}

const std::vector<std::pair<std::string, Client>>& ClientsList::getClientList() const
{
	return clientList;
}

//displays only names
void ClientsList::displayClientListNames()
{
	if (clientList.size() == 0) {
		std::cout << "No clients registered" << std::endl;
	}
	else {
		for (auto& client : clientList) {
			std::cout << client.first << std::endl;
			//std::cout << client.second.toString() << std::endl; //TODO DEBUG REMOVE
		}
	}

}