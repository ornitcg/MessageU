#pragma once
#include <string>
#include "BaseRequest.h"


class PublicKeyRequest :
    public BaseRequest
{
private:
	std::string clientId;


public:
	
	PublicKeyRequest(std::string& userName);
	~PublicKeyRequest();

	std::string getBinaryRequest();

};

