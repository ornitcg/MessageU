#pragma once
#include "BaseResponse.h"
class PublicKeyResponse :  public BaseResponse
{
private:
	std::string targetClientId ="";
	std::string targetPublicKey ="";

	void parsePayload(std::string payload);

public:
	PublicKeyResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string payload);
	virtual ~PublicKeyResponse();

	std::string getTargetPublicKey();
	std::string getTargetClientId();
};

