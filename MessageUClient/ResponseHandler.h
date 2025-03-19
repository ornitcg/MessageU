#pragma once
#include <string>
#include "Client.h"
#include "Connection.h"
#include "UImanager.h"
#include "BaseResponse.h"	
#include <fstream>
#include <iostream>


class ResponseHandler
{
private:
	Client& client;
	UImanager& uiManager;
	void saveUserInfoToFile(const std::string& clientId);


	

public:
	ResponseHandler(Client& client, UImanager& uiManager);
	~ResponseHandler();
	void receiveServerResponse();
	std::string receiveCompleteResponse();
	BaseResponse parseResponse(std::string completeResponse);
	BaseResponse& createResponse(uint8_t& version, uint16_t& code, uint32_t& payloadSize, std::string& payload);
	void useResponse(BaseResponse& response);
};

