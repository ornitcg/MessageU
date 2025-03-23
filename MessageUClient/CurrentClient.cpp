#include "CurrentClient.h"
#include "Client.h"
#include <filesystem>
#include "utils.h"
#include <fstream>
#include <iostream>
#include "EncryptionManager.h"

CurrentClient::CurrentClient() : Client(), clientList(), symmetricKeys()
{
	loadFromFile();
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
			generateNewKeys();			
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void CurrentClient::saveToFile() 
{
	try {
		//std::string filename = "me" + std::to_string(rand() % 1000) + ".info"; //TODO remove
		std::ofstream file(ME_INFO, std::ios::binary);
		if (!file) {
			throw std::runtime_error("Error: failed to open file " + std::string(ME_INFO));
		}
		file << getUserName() << std::endl;
		file << getClientId() << std::endl;
		file << getEncodedToBase64PrivateKey() << std::endl;
		file.close();
	}
	catch (const std::exception& e) {
		std::cout << "Error saving user info to file: " << e.what() << std::endl;
	}
}

void CurrentClient::generateNewKeys()
{
	if (!encMngr.generateAndSaveRSAKeys()) {
		throw std::runtime_error("Error: RSA key generation failed");
	}
}

void CurrentClient::setClientsList(std::vector<std::pair<std::string, Client>>& clientList)
{
	this->clientList = clientList;
}

const std::vector<std::pair<std::string, Client>>& CurrentClient::getClientList() const
{
	return clientList;
}

void CurrentClient::addSymmetricKey(const std::string& clientId, const std::string& key)
{
	symmetricKeys[clientId] = key;
}

std::string CurrentClient::getSymmetricKey(const std::string& clientId) const
{
	auto it = symmetricKeys.find(clientId);
	if (it != symmetricKeys.end()) {
		return it->second;
	}
	return "";
}

bool CurrentClient::hasSymmetricKey(const std::string& clientId) const
{
	return symmetricKeys.find(clientId) != symmetricKeys.end();

}

void CurrentClient::updateClientList(const std::vector<std::pair<std::string, Client>>& newClientList)
{
	clientList = newClientList;
}
