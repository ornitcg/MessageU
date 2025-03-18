#include "BaseRequest.h"
#include <WinSock2.h>
#include <iostream>
#include "utils.h"	


BaseRequest::BaseRequest(uint16_t requestCode, uint32_t payloadSize)
{	
	this->requestCode = requestCode;
	this->payloadSize = payloadSize;
}

BaseRequest::~BaseRequest()
{
}


void BaseRequest::send() {
}

std::string BaseRequest::getBinaryHeader() 
{
	std::cout << "in getBinaryHeader\n"; //DEBUG
	std::string binaryData = "";
	std::string binaryUUID = clientId.getBinary();
	std::cout << "binaryUUID: " << binaryUUID << std::endl; //DEBUG

	binaryData.append(binaryUUID);
	binaryData.append(reinterpret_cast<const char*>(&version), sizeof(version));
	std::string codeLE = toLittleEndian16string(requestCode);
	binaryData.append(codeLE);
	std::string payloadSizeLE = toLittleEndian32string(payloadSize);	
	binaryData.append(payloadSizeLE);
	std::cout << "binaryHeader: " << binaryData << std::endl; //DEBUG
	return binaryData;
}

std::string BaseRequest::getBinaryRequest()  //maybe not needed
{/*
	std::string binaryData = "";
	binaryData.append(getBinaryHeader());
	return binaryData;*/
	return "";
}


