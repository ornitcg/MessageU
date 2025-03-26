#pragma once
#include "BaseResponse.h"

class RegisterResponse : public BaseResponse
{
private:
	std::string clientId = "" ;	

public:
	RegisterResponse(const BaseResponse& header, std::string payload);
	virtual ~RegisterResponse();
	std::string getClientId();
	virtual void parsePayload(std::string payload);
};

