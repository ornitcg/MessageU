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

	void testKeys(std::string privateKey, std::string publicKey);	


	std::string encryptedWithTargetPublicKey(const std::string& PubKey, const std::string& somethingtoEncrypt);

	std::string decryptedWithMyPrivateKey(const std::string& PrivateKey, const std::string& encryptedSomething);

	std::string generateSymmetricKey();

	std::string encryptWithSymmetricKey(std::string& symKey, std::string& textMessage);

	std::string decryptWithSymmetricKey(std::string& symKey, std::string& encryptedContent);
	
};

