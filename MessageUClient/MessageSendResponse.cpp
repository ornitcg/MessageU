#include "MessageSendResponse.h"
#include <string>
#include "utils.h"

MessageSendResponse::MessageSendResponse(const BaseResponse& header, std::string payload)
	: BaseResponse(header.getVersion(),header.getCode(),header.getPayloadSize())
{
	try {
		if (payload.size() > 0)
			parsePayload(payload);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		throw e;
	}
}
	
MessageSendResponse::~MessageSendResponse()
{
}


void MessageSendResponse::parsePayload(std::string payload)
{	
	targetClientId.resize(CLIENT_ID_SIZE);
	memcpy(&targetClientId[0], payload.data(), CLIENT_ID_SIZE);
	memcpy(&messageID, payload.data()+ CLIENT_ID_SIZE, MESSAGE_ID_SIZE);
	messageID = toLittleEndian32(messageID);

	//print target client id size
	std::cout << "Target client id size: " << targetClientId.size() << std::endl; //TODO REMOVE
	//print target client id
	std::cout << "Target client id: " << targetClientId << std::endl; //TODO REMOVE

}

std::string MessageSendResponse::getTargetClientId()
{
	return targetClientId;
}

uint32_t MessageSendResponse::getMessageID()
{
	return messageID;
}

