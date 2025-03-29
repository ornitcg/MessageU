#pragma once
#include "BaseRequest.h"
#include "Message.h"


class MessageSendRequest : public BaseRequest
{
private:
	Message message;


public:
	MessageSendRequest(std::string clientID, uint16_t code, uint32_t payloadSize, Message message);
	MessageSendRequest();
	~MessageSendRequest();
	std::string getBinary();


};

