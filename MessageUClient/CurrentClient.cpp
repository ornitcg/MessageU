#include "CurrentClient.h"
#include "Client.h"
#include <filesystem>
#include "utils.h"
#include <fstream>
#include <iostream>
#include "EncryptionManager.h"

CurrentClient::CurrentClient() : Client(), clientList()
{	
	loadFromFile();
}


CurrentClient::CurrentClient(std::pair<std::string, std::string> rsaKeys) : Client(), clientList()
{
	setRSAKeys(rsaKeys);
}


CurrentClient::~CurrentClient()
{
	
}

void CurrentClient::loadFromFile()
{
	// if ME_INFO exists take private key from file
	try {
		if (std::filesystem::exists(ME_INFO)) {
			std::ifstream file(ME_INFO, std::ios::binary);
			if (!file) {
				throw std::runtime_error("Error: failed to open file " + std::string(ME_INFO));
			}
			else { // set from file
				std::string line;
				std::getline(file, line);
				setUserName(line);
				std::getline(file, line);
				setClientID(line);
				// get private key from multiline
				std::string key;
				while (true)
				{
					std::getline(file, line);
					if (line.empty())
						break;
					key += line;
				}
				setPrivateKey(key);
			}
		}
		else {// there is no ME_INFO file so generate keys
			throw std::runtime_error("Error: user info file does not exist");
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		throw e;
	}
}


void CurrentClient::saveToFile(EncryptionManager& encMngr) 
{
	try {
		//std::string filename = "me" + std::to_string(rand() % 1000) + ".info"; //TODO remove
		std::ofstream file(ME_INFO, std::ios::binary);
		if (!file) {
			throw std::runtime_error("Error: failed to open file " + std::string(ME_INFO));
		}
		std::string encodedPrivateKey = encMngr.encodeToBase64(privateKey);

		file << getUserName() << std::endl;
		file << getClientId() << std::endl;
		file << encodedPrivateKey << std::endl;
		file.close();
	}
	catch (const std::exception& e) {
		std::cout << "Error saving user info to file: " << e.what() << std::endl;
	}
}


void CurrentClient::setClientsList(std::vector<std::pair<std::string, Client>> clientList)
{
	this->clientList = clientList;
}

const std::vector<std::pair<std::string, Client>>& CurrentClient::getClientList() const
{
	return clientList;
}



std::string CurrentClient::getSymmetricKey(const std::string& userName) const
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

bool CurrentClient::hasSymmetricKey(const std::string& userName) const
{
	if (getSymmetricKey(userName).empty()) {
		return false;
	}
}

void CurrentClient::updateTargetPublicKey(const std::string& targetClientId, const std::string& targetPublicKey)
{
	for (auto& client : clientList) {
		Client& targetClient = client.second;
		if (targetClient.getClientId() == targetClientId) {
			targetClient.setPublicKey(targetPublicKey);
			std::cout << "Public key received for " <<  client.first << std::endl;
			break;
		}
	}
}



//Adds to clients list, clients that their user name does not appear in it
void CurrentClient::updateClientList(const std::vector<std::pair<std::string, Client>>& newClientList)
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
std::string CurrentClient::getTargetClientIdByName(const std::string& userName) const
{
	for (auto client : clientList) {
		if (client.first == userName) {
			return client.second.getClientId();
		}
	}
	throw std::runtime_error("Error: client not found");
}

//finds the Client object
Client CurrentClient::getTargetClientByUserName(std::string userName) const
{
	for (auto client : clientList) {
		if (client.first == userName) {
			return client.second;
		}
	}
	throw std::runtime_error("Error: client not found");
}

void CurrentClient::setRSAKeys(std::pair<std::string,std::string> rsaKeys)
{
	setPrivateKey(rsaKeys.first);
	setPublicKey(rsaKeys.second);
}

void CurrentClient::setPrivateKey(std::string& privateKey)
{
	this-> privateKey = privateKey;
}

