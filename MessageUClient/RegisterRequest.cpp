#include "RegisterRequest.h"
#include "RequestInfo.h"
#include <iostream>
#include <cstring>


RegisterRequest::RegisterRequest(std::string& userName) : BaseRequest(static_cast<uint16_t>(RequestCode::REGISTER))
{
	std::cout << "in RegisterRequest constructor\n"; //DEBUG	
	padName( userName );
	std::cout << "name: " << nameBuffer << std::endl; //DEBUG
}

RegisterRequest::~RegisterRequest()
{
}


void RegisterRequest::padName(const std::string& userName) {
	std::cout << "in padName\n"; //DEBUG
	// check if name is too long
	std::cout << "set zeos in name buffer" << std::endl; //DEBUG
	strncpy_s(nameBuffer, MAX_NAME_SIZE, userName.c_str(),  _TRUNCATE);
	std::cout << "nameBuffer: " << nameBuffer << std::endl; //DEBUG
}

std::string RegisterRequest::getBinary() const
{
	std::cout << "in getBinary\n"; //DEBUG
	std::string binaryData = getBinaryHeader();
	//add nameBuffer as binary
	binaryData.append(nameBuffer, MAX_NAME_SIZE+1);

	std::cout << "binaryData: " << binaryData << std::endl; //DEBUG
	return binaryData;
}