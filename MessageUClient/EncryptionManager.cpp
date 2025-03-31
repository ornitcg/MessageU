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


void EncryptionManager::testKeys(std::string privateKey, std::string publicKey) {
	std::string msg = "hello world";
	std::cout << "original: " << msg <<  std::endl;
	std::string encrypted = encryptWithTargetPublicKey(publicKey, msg);
	std::cout << "encrypted with public: " << encrypted << std::endl;
	std::string decrypted = decryptedWithMyPrivateKey(privateKey, encrypted);
	std::cout << "decrypted: " << decrypted << std::endl;
}






std::string EncryptionManager::encryptWithTargetPublicKey(const std::string& PubKey, const std::string& somethingToEncrypt)
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
		throw e;
	}

}

std::string EncryptionManager::generateSymmetricKey()
{
	AESWrapper aes = AESWrapper();
	unsigned char keyBuffer[AESWrapper::DEFAULT_KEYLENGTH];
	AESWrapper::GenerateKey(keyBuffer, AESWrapper::DEFAULT_KEYLENGTH);
	std::string keyString(reinterpret_cast<char*>(keyBuffer), AESWrapper::DEFAULT_KEYLENGTH );
	return keyString;
}



std::string EncryptionManager::encryptWithSymmetricKey(std::string& symKey, std::string& plainContent)
{
	AESWrapper aesWrapper = AESWrapper(reinterpret_cast<const unsigned char*>(symKey.c_str()), static_cast<unsigned int>(symKey.size()));
	std::string encryptedContent = aesWrapper.encrypt(plainContent.c_str(), static_cast<unsigned int>(plainContent.size()));
	return encryptedContent;
}

std::string EncryptionManager::decryptWithSymmetricKey(std::string& symKey, std::string& encryptedContent)
{
	AESWrapper aesWrapper = AESWrapper(reinterpret_cast<const unsigned char*>(symKey.c_str()), static_cast<unsigned int>(symKey.size()));
	std::string decryptedContent = aesWrapper.decrypt(encryptedContent.c_str(), static_cast<unsigned int>(encryptedContent.size()));
	return decryptedContent;
}

