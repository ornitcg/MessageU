#pragma once
#include <string>
#include "BaseRequest.h"


class PublicKeyRequest :
    public BaseRequest
{
private:
	std::string payloadClientId;


public:
	
	PublicKeyRequest(std::string& payloadClientId);
	~PublicKeyRequest();

	std::string getBinaryRequest();

};

