#pragma once
#include "utils.h"
#include "Connection.h"
#include "EncryptionManager.h"

class Client
{
private:
	const Connection& conn ;
	EncryptionManager encMngr;
	std::string clientId = "";
	std::string userName = "";	
	std::vector<std::string> clientsList; //list of clientNamess
	
	
	void setPublicKey(std::string& publicKey);

	
		

public:
	Client(const Connection& conn);
	~Client();
	void setUserName(std::string& userName);
	void unsetUserName();
	std::string& getUserName() ;
	std::string& getPublicKey();
	std::string& getClientId();
	const Connection& getConnection();
	void setClientID(const std::string& clientId);
	void setPrivateKey(const std::string& keyString);
	std::string& getPrivateKey();
	std::string getEncodedToBase64PrivateKey();
};

