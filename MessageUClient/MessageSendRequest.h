#pragma once
#include "BaseRequest.h"



class MessageSendRequest : public BaseRequest
{
private:
	std::string targetClientId = targetClientId;
	uint8_t messageType = messageType;
	uint32_t contentSize = contentSize;
	std::string content = content;


public:
	MessageSendRequest(uint32_t payloadSize ,std::string& currenClientId, std::string& targetClientId, uint8_t messageType, uint32_t contentSizem, std::string content);
	~MessageSendRequest();
	std::string getBinary();


};

