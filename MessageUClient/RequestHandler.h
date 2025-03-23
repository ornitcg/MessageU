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
#include "CurrentClient.h"
#include "Connection.h"
#include "UImanager.h"

//create enum for menu options

class RequestHandler
{
private:		
	const Connection& conn;
	CurrentClient& currentClient;
	UImanager& uiManager;
	
	std::string getRegisterClientBinaryRequest();
	std::string getClientsListBinaryRequest();
	std::string getPublicKeyBinaryRequest();
	void requestWaitingMessages();
	void sendTextMessage();
	void requestSymmetricKey();
	void sendSymmetricKey();

	void sendBinaryData(std::string& binaryData);

	//std::string getPublicKeyBinaryRequest();



public:
	RequestHandler(const Connection& conn, CurrentClient& currentClient, UImanager& uiManager);
	~RequestHandler();
	
	bool handleChoice(const int choice);

};

