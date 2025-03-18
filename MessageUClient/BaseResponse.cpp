#include "BaseResponse.h"

BaseResponse::BaseResponse(uint8_t version, uint16_t code, uint32_t payloadSize)
{
	this->version = version;
	this->code = code;
	this->payloadSize = payloadSize;
}

BaseResponse::~BaseResponse()
{
}

//getters
uint8_t BaseResponse::getVersion()
{
	return version;
}

uint16_t BaseResponse::getCode()
{
	return code;
}

uint32_t BaseResponse::getPayloadSize()
{
	return payloadSize;
}


