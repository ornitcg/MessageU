#pragma once
#include <string>
#include "BaseRequest.h"


class PublicKeyRequest :
    public BaseRequest
{
private:
	std::string targetClientId;


public:
	
	PublicKeyRequest(std::string& currentClientId ,std::string& payloadClientId);
	~PublicKeyRequest();

	std::string getBinaryRequest();

};

