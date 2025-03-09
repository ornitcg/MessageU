#pragma once
#include <map>
#include <string>
#include "ClientProfile.h"
#include "RequestInfo.h"
#include <WinSock2.h>   
#include <windows.h>   
#include <iostream>

//create enum for menu options




class Client
{
private:
	// Client data and connections
	
	ClientProfile clientProfile;
	SOCKET clientSocket;
	std::map<std::string, std::string> clientsList;
	std::map<std::string, std::string> symmetricKeys;
	
	void registerClient();
	void requestClientsList();
	void requestPublicKey();
	void requestWaitingMessages();
	void sendTextMessage();
	void requestSymmetricKey();
	void sendSymmetricKey();



public:
	Client(SOCKET clientSocket);
	~Client();
	int getChoice();
	void handleChoice(const MenuOption choice);
	std::string getUserNameFromConsole();

	

};

