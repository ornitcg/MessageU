#pragma once
#include "RegisterResponse.h"
#include <vector>

class ListResponse :
    public RegisterResponse
{
public:
	ListResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string payload);
	~ListResponse();
	void parsePayload(std::string payload);
	std::vector<std::string> displayClientList();


};

