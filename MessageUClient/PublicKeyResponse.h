#pragma once
#include "BaseResponse.h"
class PublicKeyResponse :  public BaseResponse
{
private:
	std::string targetClientId ="";
	std::string targetPublicKey ="";

	void parsePayload(std::string& payload);

public:
	PublicKeyResponse(const BaseResponse& header, std::string& payload);
	virtual ~PublicKeyResponse();

	std::string getTargetPublicKey();
	std::string getTargetClientId();
};

