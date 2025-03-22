#include "ListResponse.h"
#include "utils.h"

ListResponse::ListResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string payload)
	: RegisterResponse(version, code, payloadSize, payload)
{	
}

ListResponse::~ListResponse()
{
}

void ListResponse::parsePayload(std::string payload)
{
	
}

std::vector<std::string> ListResponse::displayClientList()
{
	return std::vector<std::string>();
}
