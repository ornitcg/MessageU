#pragma once
#include "RegisterResponse.h"
#include <vector>

class ListResponse :
    public RegisterResponse
{
private:
	std::vector<std::pair<std::string, std::string>> clientList;
	void parsePayload(std::string payload);

public:
	ListResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string payload);
	~ListResponse();
	void displayClientList();
	void sortClientList();

};

