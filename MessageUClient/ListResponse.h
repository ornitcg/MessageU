#pragma once
#include "RegisterResponse.h"
#include <vector>
#include "Client.h"

class ListResponse :  public RegisterResponse
{
private:
	std::vector<std::pair<std::string, Client>> clientList;
	void parsePayload(std::string payload);

public:
	ListResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string payload);
	~ListResponse();
	void displayClientListNames();
	void sortClientList();
	std::vector<std::pair<std::string, Client>> getClientList();
};

