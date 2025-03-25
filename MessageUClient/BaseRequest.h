#pragma once
#include <cstdint>
#include "utils.h"
#include <string>

//fits for 601, 604  TODO DEBUG
class BaseRequest 
{
protected:
	std::string clientId;
	uint8_t version;
	uint16_t requestCode;
	uint32_t payloadSize; 

public:
	std::string getBinaryHeader() ;
	//BaseRequest(uint16_t requestCode, std::string& clientId);
	BaseRequest(std::string& clientId, uint16_t requestCode, uint32_t payloadSize);
	virtual ~BaseRequest();
	void setClientId(std::string& clientId);
};


