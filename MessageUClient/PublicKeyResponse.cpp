#include "PublicKeyResponse.h"
#include <string>
#include "utils.h"

PublicKeyResponse::PublicKeyResponse(const BaseResponse& header, std::string& payload)
	: BaseResponse(header.getVersion(), header.getCode(), header.getPayloadSize())
{
	try {
		parsePayload(payload);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}	


PublicKeyResponse::~PublicKeyResponse()
{
}

std::string PublicKeyResponse::getTargetPublicKey() 
{
	return targetPublicKey;
}

std::string PublicKeyResponse::getTargetClientId() 
{
	return targetClientId;
}


void PublicKeyResponse::parsePayload(std::string& payload)
{	
	this -> targetClientId = payload.substr(0, CLIENT_ID_SIZE);
	this -> targetPublicKey = payload.substr(CLIENT_ID_SIZE, PUBLIC_KEY_SIZE);
}