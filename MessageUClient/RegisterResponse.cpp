#include "RegisterResponse.h"
#include "utils.h"
#include <iostream>
#include <fstream>




RegisterResponse::RegisterResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string payload)
	: BaseResponse(version, code, payloadSize)
{
	parsePayload(payload);
}

RegisterResponse::~RegisterResponse()
{
}

std::string RegisterResponse::getClientId()
{
	return clientId;
}

void RegisterResponse::parsePayload(std::string payload) {
	if (payload.size() < CLIENT_ID_SIZE) {
		throw std::runtime_error("Error: payload size is too small");
	}
	clientId.resize(CLIENT_ID_SIZE);
	memcpy(&clientId[0], payload.data(), CLIENT_ID_SIZE);
}



