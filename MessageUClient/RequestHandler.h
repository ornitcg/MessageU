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
	EncryptionManager encMngr;
	
	std::string registerClientBinaryRequest();
	std::string clientsListBinaryRequest();
	std::string publicKeyBinaryRequest();
	std::string WaitingMessagesBinaryRequest();
	std::string sendTextMessageBinaryRequest();
	std::string symmetricKeyBinaryRequest();
	//std::string sendSymmetricKeyBinaryRequest();

	void sendBinaryData(std::string& binaryData);

	//std::string getPublicKeyBinaryRequest();



public:
	RequestHandler(const Connection& conn, CurrentClient& currentClient, UImanager& uiManager, EncryptionManager& encMngr);
	~RequestHandler();
	
	bool handleChoice(const int choice);

};

