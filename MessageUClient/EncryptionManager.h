#pragma once
#include <string>
#include "RSAWrapper.h"
#include "AESWrapper.h"



class EncryptionManager
{
private:
	std::string publicKey;
	std::string privateKey;
	std::map<std::string, std::string> symmetricKeys; //client id, symmetric key

public:
	EncryptionManager();
	~EncryptionManager();

	bool generateAndSaveRSAKeys();

	bool generateAndSaveSymmetricKey(const std::string& clientId);

	std::string& getPublicKey();

};

