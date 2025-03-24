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
}


Client::~Client()
{
}



void Client::setClientID(std::string& clientId)
{
	if (this->clientId.empty())
		this->clientId = clientId;
	else throw std::runtime_error("Error: client ID already set");
}


std::string& Client::getClientId()
{
	return clientId;
}



void Client::setPublicKey(const std::string& publicKey)
{
	if (this->publicKey.empty())
		this->publicKey = publicKey;
	else throw std::runtime_error("Error: public key already set");
}

std::string& Client::getPublicKey()
{
	return publicKey;
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

std::string& Client::getUserName()
{
	return userName;
}



void Client::setSymKey(std::string& key)
{
	if (this->symKey.empty())
		this->symKey = key;
	else throw std::runtime_error("Error: symmetric key already set");
}

std::string& Client::getSymKey()
{
	return symKey;
}





