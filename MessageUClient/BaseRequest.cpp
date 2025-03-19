#include "BaseRequest.h"
#include <WinSock2.h>
#include <iostream>
#include "utils.h"	


BaseRequest::BaseRequest(uint16_t requestCode, uint32_t payloadSize)
{	
	this->clientId = std::string(16, '\0');
	this->version = SERVER_VERSION;
	this->requestCode = requestCode;
	this->payloadSize = payloadSize;
}

BaseRequest::~BaseRequest()
{
}




std::string BaseRequest::getBinaryHeader() 
{	
	std::string binaryData = "";
	binaryData.append(clientId);
	binaryData.append(reinterpret_cast<const char*>(&version), sizeof(version));
	std::string codeLE = toLittleEndian16string(requestCode);
	binaryData.append(codeLE);
	std::string payloadSizeLE = toLittleEndian32string(payloadSize);	
	binaryData.append(payloadSizeLE);	
	return binaryData;
}




