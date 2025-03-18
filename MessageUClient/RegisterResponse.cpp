#include "RegisterResponse.h"
#include "utils.h"
#include <iostream>
#include <fstream>




RegisterResponse::RegisterResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string clientId)
	: BaseResponse(version, code, payloadSize), clientId(clientId)
{
}

RegisterResponse::~RegisterResponse()
{
}

void RegisterResponse::handleResponse()
{
	std::cout << "in handleResponse of Register" << std::endl;
	//create ME_INFO file
	//write into it the user name, client id and private key
	try {
		std::ofstream file(ME_INFO, std::ios::binary);
		if (!file) {
			throw std::runtime_error("Error: failed to open file " + std::string(ME_INFO));
		}
		else {
			file << getUserName() << std::endl;
			file << clientId;
			std::cout << "Client ID: " << clientId << std::endl;
			file.close();
		
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;std::ofstream file(ME_INFO, std::ios::binary);

}
