#include "PublicKeyResponse.h"
#include <string>
#include "utils.h"

PublicKeyResponse::PublicKeyResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string payload) : BaseResponse(version, code, payloadSize)
{
	parsePayload(payload);		
}	


PublicKeyResponse::~PublicKeyResponse()
{
}

std::string PublicKeyResponse::getTargetPublicKey() 
{
	return targetPublicKey;
}

std::string PublicKeyResponse::getTargetClientId() 
{
	return targetClientId;
}


void PublicKeyResponse::parsePayload(std::string payload)
{	
	this -> targetClientId = payload.substr(0, CLIENT_ID_SIZE);
	this -> targetPublicKey = payload.substr(CLIENT_ID_SIZE, PUBLIC_KEY_SIZE);
}