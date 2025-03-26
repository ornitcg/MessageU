#include "RegisterResponse.h"
#include "utils.h"
#include <iostream>
#include <fstream>




RegisterResponse::RegisterResponse(const BaseResponse& header, std::string payload)
	: BaseResponse(header.getVersion(), header.getCode(), header.getPayloadSize())
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



