#include "EncryptionManager.h"
#include "RSAWrapper.h"
#include "AESWrapper.h"
#include "Base64Wrapper.h"
#include <filesystem>
#include "utils.h"
#include <fstream>
#include <iostream>


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

std::string& EncryptionManager::getPrivateKey() {
	return privateKey;
}

std::string EncryptionManager::getPrivateKeyToBase64() {
	return Base64Wrapper::encode(privateKey);
}

std::string EncryptionManager::getPrivateKeyFromBase64(std::string encodedPrivateKey) {
	return Base64Wrapper::decode(encodedPrivateKey);
}