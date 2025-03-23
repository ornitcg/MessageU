#include "PublicKeyResponse.h"

PublicKeyResponse::PublicKeyResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string payload) : BaseResponse(version, code, payloadSize)
{
	parsePayload(payload);
		
}	




PublicKeyResponse::~PublicKeyResponse()
{
}

std::string PublicKeyResponse::getTargetPublicKey() const
{
	return std::string();
}

std::string PublicKeyResponse::getTargetClientId() const
{
	return std::string();
}


void PublicKeyResponse::parsePayload(std::string payload) const
{
}