#include "BaseResponse.h"

BaseResponse::BaseResponse(uint8_t version, uint16_t code, uint32_t payloadSize)
{
	this->version = version;
	this->code = code;
	this->payloadSize = payloadSize;
}

BaseResponse::~BaseResponse()
{
}


void BaseResponse::handleResponse() {
	std::cout << "in handleResponse of BaseResponse" << std::endl;
}