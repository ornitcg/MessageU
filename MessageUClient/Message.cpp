#include "Message.h"
#include "utils.h"
#include "MessageSendRequest.h"

/*Data structure of a message, with  functionality of parsing*/


Message::Message()
{
}

//for received message
Message::Message(std::string& data)
{
	parseContentSize(data);
}

//for received message
Message::Message(std::string& header, std::string& content)
{
	parseHeader(header);
	this->content = content;
}


//for send
Message::Message(std::string& targetClientId, uint8_t& messageType, uint32_t& contentSize, std::string& content)
{
	this->targetClientId = targetClientId;
	this->messageType = messageType;
	this->contentSize = contentSize;
	this->content = content;
}

Message::~Message()
{
}

//received message
void Message::parseContentSize(std::string& data) {
	memcpy(&(this->contentSize), data.data() + CLIENT_ID_SIZE + MESSAGE_ID_SIZE + MESSAGE_TYPE_FIELD_SIZE , CONTENT_SIZE_FIELD_SIZE);
	this->contentSize = toLittleEndian32(this->contentSize);
}

//received message
void Message::parseHeader(std::string& header)
{
	this->targetClientId = header.substr(0, CLIENT_ID_SIZE);
	int offset = CLIENT_ID_SIZE;	
	memcpy(&(this->messageId), header.data() + offset, MESSAGE_ID_SIZE);
	this->messageId = toLittleEndian32(this->messageId);
	offset += MESSAGE_ID_SIZE;
	memcpy(&(this->messageType), header.data() + offset, MESSAGE_TYPE_FIELD_SIZE);
	offset += MESSAGE_TYPE_FIELD_SIZE;
	memcpy(&(this->contentSize), header.data() + offset, CONTENT_SIZE_FIELD_SIZE);
	this->contentSize = toLittleEndian32(this->contentSize);
}


uint32_t Message::getContentSize() {
	return contentSize;
}

uint32_t Message::getMessageId() {
	return messageId;
}

uint8_t Message::getMessageType() {
	return messageType;
}

std::string& Message::getSenderClientId() {
	return sourceClientId;
}

std::string& Message::getContent()
{
	return content;
}

std::string Message::getBinary()
{
	std::string binaryData = "";
	binaryData.append(targetClientId);
	binaryData.append(toLittleEndian32string(messageId));
	binaryData.append(toLittleEndian16string(messageType));
	binaryData.append(toLittleEndian32string(contentSize));
	binaryData.append(content);
	return binaryData;
}