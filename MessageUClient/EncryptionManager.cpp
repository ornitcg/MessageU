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

std::pair<std::string,std::string> EncryptionManager::generateRSAKeys() {
	try {
		RSAPrivateWrapper rsaPrivate = RSAPrivateWrapper();
		std::string privateKey = rsaPrivate.getPrivateKey();
		std::string publicKey = rsaPrivate.getPublicKey();
		return std::make_pair(privateKey, publicKey);
	}
	catch (const std::exception& e) {
		std::cout << "generateRSAKeys: " << e.what() << std::endl;
		throw e;
	}
	
}



std::string EncryptionManager::encodeToBase64(std::string& key) {
	return Base64Wrapper::encode(key);
}

std::string EncryptionManager::decodeFromBase64(std::string encodedKey) {
	return Base64Wrapper::decode(encodedKey);
}



std::string EncryptionManager::encryptedWithTargetPublicKey(const std::string& PubKey, const std::string& somethingToEncrypt)
{
	try {
		RSAPublicWrapper rsaPublic = RSAPublicWrapper(PubKey);
		std::string encrypted = rsaPublic.encrypt(somethingToEncrypt);
		return encrypted;
	}
	catch (const std::exception& e) {
		std::cout << "Error encoding : " << e.what() << std::endl;
		throw e;
	}
}
	
std::string EncryptionManager::decryptedWithMyPrivateKey(const std::string& privateKey, const std::string& encryptedSomething) {
	try {
		RSAPrivateWrapper rsaPrivate = RSAPrivateWrapper(privateKey);
		std::string decrypted = rsaPrivate.decrypt(encryptedSomething);
		return decrypted;
	}
	catch (const std::exception& e) {
		std::cout << "Error decoding : " << e.what() << std::endl;
		throw e;
	}

}


