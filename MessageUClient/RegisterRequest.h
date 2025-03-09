#pragma once
#include "BaseRequest.h"
#include "utils.h"
#include <string>

class RegisterRequest : public BaseRequest
{
private:
	char nameBuffer[MAX_NAME_SIZE + 1] = { 0 }; // +1 for null terminator

public:
	RegisterRequest(std::string& userName); // request code is known for register
	virtual ~RegisterRequest();
	void padName(const std::string& userName);
	std::string getBinary() const;

};

