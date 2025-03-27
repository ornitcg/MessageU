#pragma once
#include <string>
#include "EncryptionManager.h"


class Client
{
protected:
	std::string clientId = "";
	std::string userName = "";
	std::string publicKey = "";
	std::string symKey = "";

		

public:
	Client();
	Client(std::string& clientId , std::string& userName);
	virtual ~Client();

	
	std::string toString() const;

	void setUserName(const std::string& userName);
	void unsetUserName();
	std::string& getUserName();

	void setClientID(const std::string& clientId);
	std::string& getClientId();

	void setPublicKey(const std::string& publicKey);
	std::string& getPublicKey();

	void setSymKey(const std::string& key);
	std::string& getSymKey();

	bool operator<(const Client& other) const {
		return userName < other.userName;
	}

	
};

