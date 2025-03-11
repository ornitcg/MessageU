#include "RegisterResponse.h"



RegisterResponse::RegisterResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string clientId)
	: BaseResponse(version, code, payloadSize), clientId(clientId)
{
}

RegisterResponse::~RegisterResponse()
{
}

void RegisterResponse::handleResponse()
{
	std::cout << "in handleResponse of Register" << std::endl;
}
