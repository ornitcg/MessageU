#pragma once
#include <map>
#include <string>
#include "RequestInfo.h"
#include <WinSock2.h>   
#include <windows.h>   
#include <iostream>
#include "RSAWrapper.h"
#include "Base64Wrapper.h"
#include "EncryptionManager.h"
#include "Client.h"
#include "UImanager.h"

//create enum for menu options

class RequestHandler
{
private:		
	Client& client;
	UImanager& uiManager;
	
	std::string getRegisterClientBinaryRequest();
	std::string getClientsListBinaryRequest();
	void requestPublicKey();
	void requestWaitingMessages();
	void sendTextMessage();
	void requestSymmetricKey();
	void sendSymmetricKey();

	void sendBinaryData(std::string& binaryData);



public:
	RequestHandler(Client& client, UImanager& uiManager);
	~RequestHandler();
	
	bool handleChoice(const int choice);

};

