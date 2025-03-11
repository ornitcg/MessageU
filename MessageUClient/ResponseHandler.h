#pragma once
#include <string>
#include "Client.h"
#include "Connection.h"
#include "UImanager.h"
#include "BaseResponse.h"	


class ResponseHandler
{
private:
	Client& client;
	UImanager& uiManager;

	

public:
	ResponseHandler(Client& client, UImanager& uiManager);
	~ResponseHandler();
	void handleServerResponse();
	std::string receiveCompleteResponse();
	void parseResponse(std::string completeResponse);
	BaseResponse createResponse(uint8_t& version, uint16_t& code, uint32_t& payloadSize, std::string& payload);
	
};

