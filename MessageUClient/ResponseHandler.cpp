#include "ResponseHandler.h"
#include <string>

#include "utils.h"
#include "ResponseType.h"
#include "BaseResponse.h"
#include "RegisterResponse.h"
#include "client.h"
#include "UImanager.h"


ResponseHandler::ResponseHandler(Client& client, UImanager& uiManager) : client(client), uiManager(uiManager){
}

ResponseHandler::~ResponseHandler()
{
}

void ResponseHandler::receiveServerResponse() {
	std::string completeResponse = receiveCompleteResponse();
	BaseResponse response = parseResponse(completeResponse);
	useResponse(response);
	
}



std::string ResponseHandler::receiveCompleteResponse()
{
	try {//wait to get all response from server
		std::string response = "";
		char buffer[MAX_BUFF] = { 0 };
		int bytesReceived = 0;
		while (true) {
			bytesReceived = recv(client.getConnection().getClientSocket(), buffer, MAX_BUFF, 0);
			if (bytesReceived > 0) {
				response.append(buffer, bytesReceived);				
			}
			if (bytesReceived < MAX_BUFF) {
				break;
			}
			bytesReceived = 0;
		}		
		return response;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return "";
	}
}



BaseResponse ResponseHandler::parseResponse(std::string completeResponse)
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
		if (payloadSizeLE > 0) {
			payload = completeResponse.substr(SERVER_VERSION_SIZE + RESPONSE_CODE_SIZE + RESPONSE_PAYLOAD_SIZE);
			
		}		 

		// DEBUG REMOVE
		std::cout << "in parseResponse" << std::endl;
		std::cout << "parseResponse\n"  << std::endl;
		std::cout << "Version: " << static_cast<int>(version) <<std::endl;
		std::cout << "Code: " << code <<std::endl;
		std::cout << "Payload size: "  << payloadSize << std::endl;
		std::cout << "Payload: " << payload << std::endl;

		return createResponse(version, code, payloadSize, payload);
		
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}



BaseResponse ResponseHandler::createResponse(uint8_t& version, uint16_t& code, uint32_t& payloadSize, std::string& payload)
{
	BaseResponse response = BaseResponse(version, code, NO_PAYLOAD);
	try {		
		switch (static_cast<RsponseCode> (code)) {
		case RsponseCode::REGISTER_SUCEEDED: {
			std::cout << "Registration successful" << std::endl;
			response = RegisterResponse(version, code, payloadSize, payload);
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
		}
		case RsponseCode::CLIENT_LIST: {
			std::cout << "Symmetric key received" << std::endl;
			break;
		}*/
		case RsponseCode::GENERAL_ERROR: {
			std::cout << "Server responded with error" << std::endl;			
			break;
		}
		default:
			break;
		}
		return response;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		throw std::runtime_error("Failed to create any response");
	}
	
}


void ResponseHandler::useResponse(BaseResponse& response) {
	try {
		switch (static_cast<RsponseCode> (response.getCode())) {
		case RsponseCode::REGISTER_SUCEEDED: {
			RegisterResponse& regResponse = dynamic_cast<RegisterResponse&>(response);
			
			break;
		
		
		
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

