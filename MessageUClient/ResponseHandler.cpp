#include "ResponseHandler.h"
#include <string>
#include "utils.h"
#include "ResponseType.h"
#include "RequestInfo.h"
#include "BaseResponse.h"
#include "RegisterResponse.h"
#include "client.h"
#include "UImanager.h"


ResponseHandler::ResponseHandler(Client& client, UImanager& uiManager) : client(client), uiManager(uiManager){
}

ResponseHandler::~ResponseHandler()
{
}

void ResponseHandler::receiveServerResponse(int choice) {
	std::string responseHeaderString = receiveResponseHeader();
	const BaseResponse responseHeader = parseResponseHeader(responseHeaderString);
	if (responseHeader.getPayloadSize() > 0) {
		std::string payload = receivePayload(responseHeader.getPayloadSize());
		handleResponse(choice,responseHeader, payload);
	}	
}

std::string ResponseHandler::receivePayload(uint32_t payloadSize) {
	try {
		std::string payload = "";
		char buffer[MAX_BUFF] = { 0 };
		int bytesReceived = 0;
		while (true) {
			bytesReceived = recv(client.getConnection().getClientSocket(), buffer, payloadSize, 0);
			if (bytesReceived > 0) {
				payload.append(buffer, bytesReceived);
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

std::string ResponseHandler::receiveResponseHeader() {  //equivalent to BaseResponse
	try {
		std::string responseHeader = "";
		char buffer[RESPONSE_HEADER_SIZE] = { 0 };
		int bytesReceived = 0;
		while (true) {
			bytesReceived = recv(client.getConnection().getClientSocket(), buffer, RESPONSE_HEADER_SIZE, 0);
			if (bytesReceived > 0) {
				responseHeader.append(buffer, bytesReceived);
			}
			if (bytesReceived == RESPONSE_HEADER_SIZE) {
				break;
			}
			bytesReceived = 0;
		}
		return responseHeader;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return "";
	}
}


BaseResponse ResponseHandler::parseResponseHeader(std::string completeResponse)
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
		return BaseResponse(version, code, payloadSize);		
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		throw std::runtime_error("Failed to parse response");
	}
}



void ResponseHandler::handleResponse(int choice, const BaseResponse& header, std::string& payload)
{
	try {		
		switch (static_cast<RsponseCode> (header.getCode())) { //esch response object does its own payload parsing
		case RsponseCode::REGISTER_SUCEEDED: {
			std::cout << "Registration successful" << std::endl;
			RegisterResponse response = RegisterResponse(header.getVersion(), header.getCode(), header.getPayloadSize(), payload);
			this->client.setClientID(response.getClientId());
			saveUserInfoToFile();
			break;
		}		
		/*case RsponseCode::PUBLIC_KEY: {
			std::cout << "Public key received" << std::endl;
			break;
		}
		case RsponseCode::WAITING_MESSAGES: {
			std::cout << "Waiting messages received" << std::endl;
			break;
		}
		case RsponseCode::MESSAGE_SENT: {
			std::cout << "Text message received" << std::endl;
			break;
		}*/
		case RsponseCode::CLIENT_LIST: {
			std::cout << "list received" << std::endl;
			break;
		}
		case RsponseCode::GENERAL_ERROR: {
			std::cout << "Server responded with error" << std::endl;	
			if (static_cast<RequestCode>(choice) == RequestCode::REGISTER) {
				std::cout << "Registration failed" << std::endl;
				client.unsetUserName(); //revert userName to empty
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

	

void ResponseHandler::saveUserInfoToFile() {
	try {
		//std::string filename = "me" + std::to_string(rand() % 1000) + ".info"; //TODO remove
		std::ofstream file(ME_INFO, std::ios::binary);
		if (!file) {
			throw std::runtime_error("Error: failed to open file " + std::string(ME_INFO));
		}
		
		file << client.getUserName() << std::endl;
		file << client.getClientId() << std::endl;
		file << client.getEncodedToBase64PrivateKey() << std::endl;	
		file.close();
	}
	catch (const std::exception& e) {
		std::cout << "Error saving user info to file: " << e.what() << std::endl;
	}
}



