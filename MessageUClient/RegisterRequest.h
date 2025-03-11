#pragma once
#include "BaseRequest.h"
#include "utils.h"
#include <string>

class RegisterRequest : public BaseRequest
{
private:
	char nameBuffer[MAX_NAME_SIZE + 1] = { 0 }; // +1 for null terminator
	char publicKey[PUBLIC_KEY_SIZE] = { 0 };

public:
	RegisterRequest(std::string& userName, std::string& publicKey); // request code is known for register
	virtual ~RegisterRequest();
	void padName(const std::string& userName);
	std::string getBinary() const;

};

