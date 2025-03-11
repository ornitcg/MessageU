#pragma once
#include <cstdint>
#include <array>
#include "utils.h"
#include "uuid.h"

//fits for 601, 604  TODO DEBUG
class BaseRequest 
{
protected:
	myUUID clientId;
	uint8_t version = SERVER_VERSION;
	uint16_t code;
	uint32_t payloadSize = 0; 

public:
	BaseRequest(uint16_t code);
	virtual ~BaseRequest();
	void send();

	std::string getBinaryHeader() const;

	virtual std::string getBinaryRequest() const;

};

