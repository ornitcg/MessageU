#include "Message.h"
#include "utils.h"
#include "MessageSendRequest.h"
#include <iostream>

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
Message::Message(std::string& targetClientId, uint8_t& messageType, std::string& content)
{
	this->targetClientId = targetClientId;	
	this->messageType = messageType;	
	this->contentSize = static_cast<uint32_t>(content.size());	
	this->content = content;	
}

Message::~Message()
{
}

//received message
void Message::parseContentSize(std::string& data) {
	memcpy(&(this->contentSize), data.data() + CLIENT_ID_SIZE + MESSAGE_ID_SIZE + MESSAGE_TYPE_FIELD_SIZE , CONTENT_SIZE_FIELD_SIZE);
	this->contentSize = toLittleEndian32(this->contentSize);
	//print content size
	std::cout << "contentSize: " << this->contentSize << std::endl;

}

//received message
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
	binaryData.append(1, messageType);	
	binaryData.append(toLittleEndian32string(contentSize));	
	binaryData.append(content);
	return binaryData;
}