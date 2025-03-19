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
	void saveUserInfoToFile();


	

public:
	ResponseHandler(Client& client, UImanager& uiManager);
	~ResponseHandler();
	void receiveServerResponse(int choice);
	std::string receivePayload(uint32_t getPayloadSize);
	std::string receiveResponseHeader();
	BaseResponse parseResponseHeader(std::string completeResponse);
	void handleResponse(int choice, const BaseResponse& responseHeader, std::string& payload);
	
};

