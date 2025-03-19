#pragma once
#include "BaseResponse.h"

class RegisterResponse : public BaseResponse
{
private:
	std::string clientId = "" ;	

public:
	RegisterResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string clientId);
	virtual ~RegisterResponse();
	std::string getClientId();
	virtual void parsePayload(std::string payload);
};

