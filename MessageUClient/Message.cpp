#include "Message.h"
#include "utils.h"
#include "MessageSendRequest.h"

/*Data structure of a message, with little functionality of parsing*/


Message::Message(std::string& data)
{
	parseContentSize(data);
}

Message::Message(std::string& header, std::string& content)
{
	parseHeader(header);
	this->rawContent = content;
}

Message::~Message()
{
}


void Message::parseContentSize(std::string& data) {
	memcpy(&(this->contentSize), data.data() + CLIENT_ID_SIZE + MESSAGE_ID_SIZE + MESSAGE_TYPE_FIELD_SIZE , CONTENT_SIZE_FIELD_SIZE);
	this->contentSize = toLittleEndian32(this->contentSize);
}


void Message::parseHeader(std::string& header)
{
	this->sourceClientId = header.substr(0, CLIENT_ID_SIZE);
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

std::string& Message::getSourceClientId() {
	return sourceClientId;
}

std::string& Message::getRawContent()
{
	return rawContent;
}

