#pragma once
#include "BaseRequest.h"
#include "utils.h"
#include <string>

class RegisterRequest : public BaseRequest
{
private:
	char nameBuffer[MAX_NAME_SIZE + 1] = {}; // +1 for null terminator
	char publicKey[PUBLIC_KEY_SIZE + 1] = {};// +1 for null terminator

public:
	RegisterRequest(std::string& clientId,std::string& userName, std::string& publicKey, uint32_t payloadSize); // request code is known for register
	virtual ~RegisterRequest();
	void initializePublicKey(const std::string& pubKey);
	void initializeUserNameWithPadding(const std::string& userName);
	std::string getBinary() ;

};

