#include "Client.h"
#include <filesystem>
#include "utils.h"
#include <fstream>
#include <iostream>
#include "Base64Wrapper.h"

Client::Client(const Connection& conn) : conn(conn)
{	
	encMngr = EncryptionManager();
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
				std::getline(file, line);
				setPrivateKey(line);	
				// print all 3
				std::cout << "in client ctor : User name: " << getUserName() << std::endl;
				std::cout << "Client ID: " << getClientId() << std::endl;
				std::cout << "Private key: " << encMngr.getPrivateKey() << std::endl;
			}
		}
		else {// no ME_INFO file so generate keys
			if (!encMngr.generateAndSaveRSAKeys()) {
				throw std::runtime_error("Error: RSA key generation failed");
			}
		}



	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	try{
		encMngr = EncryptionManager();		
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		throw e;
	}	
}


Client::~Client()
{
}

std::string& Client::getUserName() 
{
	return userName;
}

std::string& Client::getClientId()
{
	return clientId;
}


std::string& Client::getPublicKey()
{
	return encMngr.getPublicKey();
}

std::string& Client::getPrivateKey()
{
	return encMngr.getPrivateKey();
}

std::string Client::getEncodedToBase64PrivateKey()
{
	std::string key = encMngr.getPrivateKeyToBase64();
	std::cout << "in client getEncodedToBase64PrivateKey: " << key << std::endl;
	return key;
}


void Client::setUserName(std::string& userName)
{
	if (this->userName.empty())
		this->userName = userName;
	else throw std::runtime_error("Error: user name already set");
}

void Client::unsetUserName()
{
	this->userName = "";
}

void Client::setPublicKey(std::string& publicKey)
{
}

const Connection& Client::getConnection()
{
	return conn;
}


void Client::setClientID(const std::string& clientId)
{
	if (this->clientId.empty())
		this->clientId = clientId;
	else throw std::runtime_error("Error: client ID already set");
}

void Client::setPrivateKey(const std::string& keyString)
{
	if (this->encMngr.getPrivateKey().empty())
		this->encMngr.getPrivateKey() = Base64Wrapper::decode(keyString);
	else throw std::runtime_error("Error: private key already set");
}