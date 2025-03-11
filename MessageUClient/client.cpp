#include "Client.h"

Client::Client(const Connection& conn) : conn(conn)
{	
	encMngr = EncryptionManager();
	if (!encMngr.generateAndSaveRSAKeys()) {
		throw std::runtime_error("Error: RSA key generation failed");
	}
}


Client::~Client()
{
}

std::string& Client::getUserName() 
{
	return userName;
}

std::string& Client::getPublicKey() 
{
	return encMngr.getPublicKey();
}

void Client::setUserName(const std::string& userName)
{
	if (this->userName.empty())
		this->userName = userName;
	else throw std::runtime_error("Error: user name already set");
}

void Client::setPublicKey(const std::string& publicKey)
{
}

const Connection& Client::getConnection()
{
	return conn;
}
