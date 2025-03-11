#pragma once
#include <iostream>


class BaseResponse
{
private:
	uint8_t version = 0;
	uint16_t code = 0;
	uint32_t payloadSize = 0;

public:
	BaseResponse(uint8_t version, uint16_t code, uint32_t payloadSize);
	virtual ~BaseResponse();
	
	virtual void handleResponse();
};

