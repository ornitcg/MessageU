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
	
	void setUserName(const std::string& userName);
	void setPublicKey(const std::string& publicKey);

	
		

public:
	Client(const Connection& conn);
	~Client();
	std::string& getUserName() ;
	std::string& getPublicKey();
	std::string& getClientId();
	const Connection& getConnection();
	void setClientID(const std::string& line);
	void setPrivateKey(const std::string& line);
};

