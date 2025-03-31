#pragma once
#include <string>
#include "CurrentClient.h"
#include "Connection.h"
#include "UImanager.h"
#include "BaseResponse.h"
#include "EncryptionManager.h"
#include "ClientsList.h"

#include "Message.h"



class ResponseHandler
{
private:
	const Connection& conn;
	CurrentClient& currentClient;
	UImanager& uiManager;
	ClientsList& clientsList;
	EncryptionManager encMngr;
	void saveUserInfoToFile();


	void handleRegisterResponse(const BaseResponse& header, std::string& payload);
	void handlePublicKeyRecieved(const BaseResponse& header, std::string& payload);
	void handleListResponse(const BaseResponse& header, std::string& payload);
	void handleMessageSentAckResponse(const BaseResponse& header, std::string& payload);

	void handleMessagesListResponse(const BaseResponse& header, std::string& payload);

	std::string findUserNameToDisplay(std::string& clientId);

	std::string cutPartFromData(std::string& data, size_t messageHeaderSize);

	std::string handleMessageAccordingToType(Message& message, std::string& userName);

	void handleReceivedSymmetricKey(std::string& targetClientId, std::string& encryptedSymKey);

	std::string handleTextMessage(std::string& userName, std::string& rawContent);

	std::string handleFileMessage(std::string& userName, std::string& rawContent);


	

public:
	ResponseHandler(const Connection& conn, CurrentClient& currentClient, UImanager& uiManager, ClientsList& clientsList,  EncryptionManager& encMngr);
	~ResponseHandler();
	void receiveServerResponse(int choice);
	std::string receivePayload(uint32_t getPayloadSize);
	std::string receiveResponseHeader();
	BaseResponse parseResponseHeader(std::string& completeResponse);
	void handleResponse(int choice,const  BaseResponse& responseHeader, std::string& payload);
	
};

