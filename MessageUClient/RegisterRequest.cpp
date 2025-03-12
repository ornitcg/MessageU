#include "RegisterRequest.h"
#include "RequestInfo.h"
#include <iostream>
#include <cstring>
#include "utils.h"


RegisterRequest::RegisterRequest(std::string& userName, std::string& publicKey) : BaseRequest(static_cast<uint16_t>(RequestCode::REGISTER))
{
	payloadSize = REGISTER_REQUEST_PAYLOAD_SIZE; 
	padName(userName);
	strncpy_s(this->publicKey, PUBLIC_KEY_SIZE, publicKey.c_str(), _TRUNCATE);
}

RegisterRequest::~RegisterRequest()
{
}

void RegisterRequest::padName(const std::string& userName) {
	strncpy_s(nameBuffer, MAX_NAME_SIZE, userName.c_str(),  _TRUNCATE);
}

std::string RegisterRequest::getBinary() const
{
	std::cout << "in getBinary\n"; //DEBUG
	std::string binaryData = getBinaryHeader();
	//add nameBuffer as binary
	binaryData.append(nameBuffer, MAX_NAME_SIZE+1);
	binaryData.append(this->publicKey, PUBLIC_KEY_SIZE);

	std::cout << "binaryData: " << binaryData << std::endl; //DEBUG
	return binaryData;
}