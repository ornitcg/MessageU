#include "ResponseHandler.h"
#include <string>
#include "utils.h"
#include "ResponseType.h"
#include "RequestInfo.h"
#include "BaseResponse.h"
#include "RegisterResponse.h"
#include "PublicKeyResponse.h"
#include "ListResponse.h"
#include "CurrentClient.h"
#include "UImanager.h"
#include "ClientsList.h"
#include "MessageSendResponse.h"



ResponseHandler::ResponseHandler(const Connection& conn, CurrentClient& currentClient, UImanager& uiManager, ClientsList& clientsList, EncryptionManager& encMngr):conn(conn), currentClient(currentClient), uiManager(uiManager), clientsList(clientsList), encMngr(encMngr)
{
}

ResponseHandler::~ResponseHandler()
{
}

void ResponseHandler::receiveServerResponse(int choice) {
	std::string responseHeaderString = receiveResponseHeader();
	const BaseResponse responseHeader = parseResponseHeader(responseHeaderString);
	uint32_t payloadSize = responseHeader.getPayloadSize();
	std::cout << "in receiveServerResponse : Payload size: " << payloadSize << std::endl; //TODO REMOVE
	if (payloadSize > 0) {
		std::string payload = receivePayload(responseHeader.getPayloadSize());
		//print payload
		std::cout << "in receiveServerResponse Payload: " << payload << std::endl; //TODO REMOVE
		handleResponse(choice,responseHeader, payload);
	}	
}

std::string ResponseHandler::receivePayload(uint32_t payloadSize) {
	try {
		std::string payload = "";
		char buffer[MAX_BUFF] = { 0 };
		uint32_t bytesReceived = 0;
		uint32_t bytesLeftToReceive = payloadSize;
		while (bytesReceived < payloadSize) {
			bytesReceived = recv(conn.getClientSocket(), buffer, min(MAX_BUFF, bytesLeftToReceive), 0);
			if (bytesReceived > 0) {
				payload.append(buffer, bytesReceived);
				bytesLeftToReceive -= bytesReceived;
			}
			if (payload.size() == payloadSize) {
				break;
			}
			bytesReceived = 0;
		}
		return payload;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return "";
	}
}



std::string ResponseHandler::receiveResponseHeader() {
	try {
		std::string responseHeader;
		int totalReceived = 0;
		char buffer[RESPONSE_HEADER_SIZE];

		// Keep receiving until we have the complete header
		while (totalReceived < RESPONSE_HEADER_SIZE) {
			int bytesReceived = recv(conn.getClientSocket(), buffer, RESPONSE_HEADER_SIZE - totalReceived, 0);
			std::cout << "in receiveResponseHeader Bytes received: " << bytesReceived << std::endl;

			if (bytesReceived <= 0) {
				throw std::runtime_error("Error: connection closed by server");
			}
			responseHeader.append(buffer, bytesReceived);
			totalReceived += bytesReceived;
		}

		return responseHeader;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return "";
	}
}


// parses the response header and returns a BaseResponse object
BaseResponse ResponseHandler::parseResponseHeader(std::string& completeResponse)
{
	try {
		uint8_t version = 0;
		uint16_t code = 0;
		uint32_t payloadSize = 0;
		std::string payload = "";
		memcpy(&version, completeResponse.data(), SERVER_VERSION_SIZE);

		memcpy(&code, completeResponse.data() + SERVER_VERSION_SIZE, RESPONSE_CODE_SIZE);
		uint16_t codeLE = toLittleEndian16(code);  // Convert 2-byte value
	
		memcpy(&payloadSize, completeResponse.data() + SERVER_VERSION_SIZE + RESPONSE_CODE_SIZE, RESPONSE_PAYLOAD_SIZE);
		uint32_t payloadSizeLE = toLittleEndian32(payloadSize);  // Convert 2-byte value
	
		return BaseResponse(version, codeLE, payloadSizeLE);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		throw std::runtime_error("Failed to parse response");
	}
}


//handles the response according to the response code
void ResponseHandler::handleResponse(int choice, const BaseResponse& header, std::string& payload)
{
	try {		
		switch (static_cast<RsponseCode> (header.getCode())) { //esch response object does its own payload parsing
		case RsponseCode::REGISTER_SUCEEDED: {
			handleRegisterResponse(header, payload);			
			break;
		}		
		case RsponseCode::PUBLIC_KEY: {
			handlePublicKeyRecieved(header, payload);			
			break;
		}
		/*case RsponseCode::WAITING_MESSAGES: {
			std::cout << "Waiting messages received" << std::endl;
			break;
		}*/
		case RsponseCode::MESSAGE_SENT: {
			handleMessageSentAckResponse(header, payload);
			break;
		}
		case RsponseCode::CLIENT_LIST: {
			handleListResponse(header, payload);			
			break;
		}
		case RsponseCode::GENERAL_ERROR: {
			std::cout << "Server responded with error" << std::endl;	
			if (static_cast<RequestCode>(choice) == RequestCode::REGISTER) {
				std::cout << "Registration failed" << std::endl;
				currentClient.unsetUserName(); //revert userName to empty
			}
			break;
		}
		default:
			break;
		}
		
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		throw std::runtime_error("Failed to create any response");
	}
	
}

	





void ResponseHandler::handleRegisterResponse(const BaseResponse& header, std::string& payload) {
	std::cout << "Registration successful" << std::endl;
	RegisterResponse response = RegisterResponse(header, payload);
	std::string clientId = response.getClientId();
	this->currentClient.setClientID(clientId);	
	saveUserInfoToFile();
}


void ResponseHandler::saveUserInfoToFile() {
	currentClient.saveToFile(encMngr);
}


void ResponseHandler::handlePublicKeyRecieved(const BaseResponse& header, std::string& payload) {	
	PublicKeyResponse response = PublicKeyResponse(header, payload);
	clientsList.updateTargetPublicKey(response.getTargetClientId(), response.getTargetPublicKey());
}

void ResponseHandler::handleListResponse(const BaseResponse& header, std::string& payload) {
	std::cout << "Users list:" << std::endl;
	//std::cout << payload << std::endl;
	ListResponse listResponse = ListResponse(header, payload);
	clientsList.updateClientsList(listResponse.getClientList());
	clientsList.displayClientListNames();

}


void ResponseHandler::handleMessageSentAckResponse(const BaseResponse& header, std::string& payload) {
	MessageSendResponse response = MessageSendResponse(header, payload);
	std::string userName = clientsList.getUserNameByTargetClientId(response.getTargetClientId());
	std::cout << "Message sent successfully to client: " << userName << std::endl;
	std::cout << "Message ID: " << response.getMessageID() << std::endl;

}