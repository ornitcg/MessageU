#include "MessageSendRequest.h"
#include "RequestInfo.h"
#include "BaseRequest.h"
#include <string>

MessageSendRequest::MessageSendRequest(uint32_t payloadSize,  std::string& currenClientId, std::string& targetClientId, uint8_t messageType, uint32_t contentSize , std::string content) : BaseRequest(currenClientId, static_cast<uint16_t>(RequestCode::SEND_MESSAGE), payloadSize)
{
	this->targetClientId = targetClientId;
	this->messageType = messageType;
	this->contentSize = contentSize;
	this->content = content;
}


MessageSendRequest::~MessageSendRequest()
{
}



std::string MessageSendRequest::getBinary() 
{	
	std::string binaryData = getBinaryHeader();
	binaryData.append(targetClientId);
	binaryData.append(reinterpret_cast<const char*>(&messageType), sizeof(messageType));
	uint32_t contentSizeLE = toLittleEndian32(this->contentSize);
	binaryData.append(reinterpret_cast<const char*>(&contentSizeLE), sizeof(contentSizeLE));
	binaryData.append(content);
	return binaryData;
}
