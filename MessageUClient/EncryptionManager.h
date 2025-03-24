#pragma once
#include <string>
#include "RSAWrapper.h"
#include "AESWrapper.h"



class EncryptionManager
{
private:
	

public:
	EncryptionManager();
	~EncryptionManager();

	std::pair<std::string, std::string> generateRSAKeys();
	
	std::string encodeToBase64(std::string& key);

	std::string decodeFromBase64(std::string encodedKey);

	std::string encryptedWithTargetPublicKey(const std::string& PubKey, const std::string& somethingtoEncrypt);

	std::string decryptedWithMyPrivateKey(const std::string& PrivateKey, const std::string& encryptedSomething);
	
};

