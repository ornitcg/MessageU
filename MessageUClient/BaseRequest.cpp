#include "BaseRequest.h"
#include <WinSock2.h>
#include <iostream>


BaseRequest::BaseRequest(uint16_t requestCode) 
{	
	this->code = requestCode;
}

BaseRequest::~BaseRequest()
{
}


void BaseRequest::send() {
}

std::string BaseRequest::getBinaryHeader() const
{
	std::cout << "in getBinaryHeader\n"; //DEBUG
	std::string binaryData = "";
	std::string binaryUUID = clientId.getBinary();
	std::cout << "binaryUUID: " << binaryUUID << std::endl; //DEBUG

	binaryData.append(binaryUUID);
	binaryData.append(reinterpret_cast<const char*>(&version), sizeof(version));
	binaryData.append(reinterpret_cast<const char*>(&code), sizeof(code));
	binaryData.append(reinterpret_cast<const char*>(&payloadSize), sizeof(payloadSize));
	return binaryData;
}

std::string BaseRequest::getBinaryRequest() const //maybe not needed
{
	std::string binaryData = "";
	binaryData.append(getBinaryHeader());
	return binaryData;
}


