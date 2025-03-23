#pragma once
#include "BaseResponse.h"
class PublicKeyResponse :  public BaseResponse
{
private:
	std::string targetPublicKey;
	std::string targetClientId;
	void parsePayload(std::string payload) const;



public:
	PublicKeyResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string payload);
	virtual ~PublicKeyResponse();

	std::string getTargetPublicKey() const;
	std::string getTargetClientId() const;
};

