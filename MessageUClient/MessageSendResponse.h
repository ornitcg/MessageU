#pragma once
#include "BaseResponse.h"
#include <string>



class MessageSendResponse : public BaseResponse
{
private:
	std::string targetClientId;
	uint32_t messageID = 0;
	


public:
	MessageSendResponse(const BaseResponse& header, std::string payload);
	~MessageSendResponse();

	void parsePayload(std::string payload);
	//getters
	std::string getTargetClientId();
	uint32_t getMessageID();
};

