#include "MessageSendRequest.h"
#include "RequestInfo.h"
#include "BaseRequest.h"
#include <string>


MessageSendRequest::MessageSendRequest(std::string clientID, uint16_t code, uint32_t payloadSize, Message message)
	:BaseRequest(clientID, code, payloadSize)
{
	this->message = message;
}

//default constructor
MessageSendRequest::MessageSendRequest()
	:BaseRequest()
{
}

MessageSendRequest::~MessageSendRequest()
{
}



std::string MessageSendRequest::getBinary() 
{	
	std::string binaryData = getBinaryHeader();
	binaryData.append(message.getBinary());
	return binaryData;
}
