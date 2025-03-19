#include "RegisterResponse.h"
#include "utils.h"
#include <iostream>
#include <fstream>




RegisterResponse::RegisterResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string clientId)
	: BaseResponse(version, code, payloadSize), clientId(clientId)
{
}

RegisterResponse::~RegisterResponse()
{
}

std::string RegisterResponse::getClientId()
{
	return clientId;
}


