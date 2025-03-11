#pragma once
#include "utils.h"
#include "Connection.h"
#include "EncryptionManager.h"

class Client
{
private:
	const Connection& conn ;
	EncryptionManager encMngr;
	std::string clientID = "";
	std::string userName = "";	
	std::vector<std::string> clientsList; //list of clientNamess
	
	void setUserName(const std::string& userName);
	void setPublicKey(const std::string& publicKey);

	
		

public:
	Client(const Connection& conn);
	~Client();
	std::string& getUserName() ;
	std::string& getPublicKey() ;
	const Connection& getConnection();
};

