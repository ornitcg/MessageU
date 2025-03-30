#pragma once
#include <string>



class Message
{
private:
	std::string sourceClientId; // recv
	std::string targetClientId;  // send
	uint32_t messageId = 0;  // recv
	uint8_t messageType = 0;
	uint32_t contentSize = 0;
	std::string content ;

public:
	Message();
	Message(std::string& header);
	Message(std::string& header, std::string& content);
	Message(std::string& sourceClientId,  uint8_t& messageType,  std::string& content);

	~Message();

	void parseContentSize(std::string& data);
	void parseHeader(std::string& header);
	uint32_t getContentSize();
	uint32_t getMessageId();
	uint8_t getMessageType();
	std::string& getSenderClientId();
	std::string& getContent();
	std::string getBinary();
};

