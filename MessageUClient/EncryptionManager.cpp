#include "EncryptionManager.h"
#include "RSAWrapper.h"
#include "AESWrapper.h"

EncryptionManager::EncryptionManager()
{
}

EncryptionManager::~EncryptionManager()
{
}


bool EncryptionManager::generateAndSaveRSAKeys() {
	try {
		RSAPrivateWrapper rsaPrivate = RSAPrivateWrapper();
		privateKey = rsaPrivate.getPrivateKey();
		publicKey = rsaPrivate.getPublicKey();
		return true;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	}
}

bool EncryptionManager::generateAndSaveSymmetricKey(const std::string& clientId) {
	return false; //TODO
}

std::string& EncryptionManager::getPublicKey() {
	return publicKey;
}
