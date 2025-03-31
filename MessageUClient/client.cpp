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



void Client::setClientID(const std::string& clientId)
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
	else std::cout << "Public key already set for this user" << std::endl;
}

std::string& Client::getPublicKey()
{
	if (publicKey.empty()) {
		throw std::runtime_error("Error: Request for public key, of this user, first");
	}
	return publicKey;
}


std::string Client::toString() const
{
	std::string str = "User name: " + userName;
	str += "   Client ID: " + clientId;	
	str += "   Public key: " + publicKey;
	return str;
}

void Client::setUserName(const std::string& userName)
{
	/*if (this->userName.empty())*/
		this->userName = userName;
	/*else 
		throw std::runtime_error("Error: user name already set");*/
}

void Client::unsetUserName()
{
	this->userName = "";
}

std::string& Client::getUserName()
{
	return userName;
}



void Client::setSymKey(const std::string& symmetricKey)
{
	if (this->symKey.empty())
		this->symKey = symmetricKey;
	else throw std::runtime_error("Error: symmetric key already set");
}

//std::string& Client::getSymKey()
//{
//	return symKey;
//}





std::string& Client::getSymKey()
{
	if (symKey.empty()) {
		throw std::runtime_error("Error: Request for symKey , of this user, first");
	}
	return symKey;
}

bool Client::wasSymKeyRequested()
{
	return symKeyRequested;
}

void Client::setSymKeyRequested(bool value)
{
	symKeyRequested = value;
}
