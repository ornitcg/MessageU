#include "CurrentClient.h"
#include "Client.h"
#include <filesystem>
#include "utils.h"
#include <fstream>
#include <iostream>
#include "EncryptionManager.h"

CurrentClient::CurrentClient() : Client() 
{	
	loadFromFile();
}


CurrentClient::CurrentClient(std::pair<std::string, std::string> rsaKeys) : Client()
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
				bool firstLine = true;
				while (true)
				{
					std::getline(file, line);
					if (line.empty())
						break;
					if (!firstLine) {
						key += "\n";
					}
					key += line;
					firstLine = false;
				}
				setPrivateKey(key);
			}
		}
		else {// there is no ME_INFO file so generate keys
			throw std::runtime_error("ME.INFO not found");
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

void CurrentClient::setRSAKeys(std::pair<std::string,std::string> rsaKeys)
{
	setPrivateKey(rsaKeys.first);
	setPublicKey(rsaKeys.second);
}

void CurrentClient::setPrivateKey(std::string& privateKey)
{
	this-> privateKey = privateKey;
}

std::string& CurrentClient::getPrivateKey()
{
	return privateKey;
}



