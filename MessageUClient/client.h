#pragma once
#include <string>
#include "EncryptionManager.h"


class Client
{
protected:
	//EncryptionManager encMngr;
	std::string clientId = "";
	std::string userName = "";
	EncryptionManager encMngr;

		

public:
	Client();
	Client(std::string& clientId , std::string& userName);
	virtual ~Client();
	void setUserName(std::string& userName);
	void unsetUserName();
	virtual std::string& getUserName() ;
	virtual std::string& getPublicKey();
	virtual std::string& getClientId();
	void setClientID(const std::string& clientId);
	void setPrivateKey(const std::string& keyString);
	virtual std::string& getPrivateKey();
	virtual std::string getEncodedToBase64PrivateKey();
	void setPublicKey(const std::string& publicKey);


	bool operator<(const Client& other) const {
		return userName < other.userName;
	}

	
};

