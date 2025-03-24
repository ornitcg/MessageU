#pragma once
#include "BaseRequest.h"



class MessageRequest : public BaseRequest
{
private:
	std::string targetClientId = targetClientId;
	uint8_t messageType = messageType;
	uint32_t contentSize = contentSize;
	std::string content = content;


public:
	MessageRequest( std::string& currenClientId, std::string& targetClientId, uint8_t messageType, uint32_t contentSizem, std::string content);
	~MessageRequest();
	std::string getBinary();


};

