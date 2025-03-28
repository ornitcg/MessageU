#include "RegisterRequest.h"
#include "RequestInfo.h"
#include <iostream>
#include <cstring>
#include "utils.h"


RegisterRequest::RegisterRequest(std::string& clientId, std::string& userName, std::string& pubKey, uint32_t payloadSize) : BaseRequest(clientId, static_cast<uint16_t>(RequestCode::REGISTER), payloadSize)
{
	initializeUserNameWithPadding(userName);
	initializePublicKey(pubKey);	
}

RegisterRequest::~RegisterRequest()
{
}


void RegisterRequest::initializeUserNameWithPadding(const std::string& userName) {
	size_t userNameSize = userName.size();
	memset(nameBuffer, '0', MAX_NAME_SIZE + 1);
	if (userNameSize > MAX_NAME_SIZE) {
		throw std::runtime_error("Error: user name is too long");
	}
	strncpy_s(nameBuffer, MAX_NAME_SIZE + 1, userName.c_str(),  _TRUNCATE);
}


void RegisterRequest::initializePublicKey(const std::string& pubKey) {
	memset(this->publicKey, '\0', PUBLIC_KEY_SIZE + 1);
	memcpy(this->publicKey, pubKey.c_str(),  (size_t)PUBLIC_KEY_SIZE);
}


std::string RegisterRequest::getBinary() 
{
	std::string binaryData = getBinaryHeader();
	binaryData.append(nameBuffer, MAX_NAME_SIZE+1);
	size_t currentSize = binaryData.size();
	size_t totalsize = currentSize + PUBLIC_KEY_SIZE + 1;
	binaryData.resize(totalsize);
	memcpy(&binaryData[currentSize], this->publicKey, PUBLIC_KEY_SIZE);
	return binaryData;
}