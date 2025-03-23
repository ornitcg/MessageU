#include "Client.h"
#include <filesystem>
#include "utils.h"
#include <fstream>
#include <iostream>
#include "Base64Wrapper.h"
#include "EncryptionManager.h"



Client::Client() 
{		
}

Client::Client(std::string& clientId, std::string& userName)
{
	this->clientId = clientId;
	this->userName = userName;
	this->encMngr = EncryptionManager();
}


Client::~Client()
{
	this->encMngr = EncryptionManager();
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
	return key;
}


void Client::setUserName(std::string& userName)
{
	if (this->userName.empty())
		this->userName = userName;
	else 
		throw std::runtime_error("Error: user name already set");
}

void Client::unsetUserName()
{
	this->userName = "";
}

void Client::setPublicKey(std::string& publicKey)
{
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

