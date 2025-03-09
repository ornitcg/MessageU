#pragma once
#include "BaseRequest.h"
class TargetClientRequest : public BaseRequest
{
private:
	myUUID targetClientId;


public:
	TargetClientRequest(uint16_t requestCode);
	~TargetClientRequest();
};

