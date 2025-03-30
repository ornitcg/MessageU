#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "utils.h"
#include <vector>
#include <array>
#include <iomanip>

//returns array with IP and port, read from file
std::array<std::string,2> getServerIPfromFile(std::string fileName) {
	std::string serverIP = "";
	std::string port = "";
	std::string line;
	std::ifstream file(fileName, std::ios::binary);
	if (!file) {
		std::cerr << "Failed to open file " << fileName << std::endl;
	}
	else if (std::getline(file, line)){
		std::stringstream ss(line);
		std::getline(ss, serverIP, ':');
		std::getline(ss, port);
		
	}
	return{ serverIP, port };
}




std::string toLittleEndian32string(uint32_t value) {
	std::string result= "";
	if (!isLittleEndian()) {
		result[0] = value & 0xFF;
		result[1] = (value >> 8) & 0xFF;
		result[2] = (value >> 16) & 0xFF;
		result[3] = (value >> 24) & 0xFF;
	}
	char* valuePtr = reinterpret_cast<char*>(&value);	
	result.push_back(valuePtr[0]);
	result.push_back(valuePtr[1]);
	result.push_back(valuePtr[2]);
	result.push_back(valuePtr[3]);
	return result;
}

std::string toLittleEndian16string(uint16_t value) {	
	std::string result = "";
	if (!isLittleEndian()) {
		result[0] = value & 0xFF;
		result[1] = (value >> 8) & 0xFF;		
	}
	char* valuePtr = reinterpret_cast<char*>(&value);	
	result.push_back(valuePtr[0]);
	result.push_back(valuePtr[1]);	
	return result;
}


void printAsHex(const std::string& binaryData) {
	for (unsigned char byte : binaryData) {
		// Convert each byte to a two-digit hex number
		std::cout << std::hex << std::setw(2) << std::setfill('0')
			<< static_cast<int>(byte) << " ";
	}
	std::cout << std::dec << std::endl; // Reset to decimal output
}


uint16_t toLittleEndian16(uint16_t value) {
	if (isLittleEndian()) { //no conversion needed
		return value;
	}
	else {		
		return ((value & 0xFF) << 8) | ((value >> 8) & 0xFF);
	}
}

uint32_t toLittleEndian32(uint32_t value) {
	if (isLittleEndian()) {//no conversion needed
		return value;
	}	
	return ((value & 0xFF) << 24) | ((value & 0xFF00) << 8) | ((value & 0xFF0000)  >> 8) | ((value & 0xFF000000) >> 24);
}

bool isLittleEndian() {
	static const uint16_t test = 0x0001;
	return (*reinterpret_cast<const uint8_t*>(&test) == 1);
}

std::string trimNonPrintableChars(const std::string& str)
{
	size_t firstPrintable = 0;
	
	while (firstPrintable < str.length() && (str[firstPrintable] < 32 || str[firstPrintable] > 126)) {
		firstPrintable++;
	}
	return  str.substr(firstPrintable);
}

std::string removeZeroPadding(const std::string& str)
{
	size_t nullPos = str.find('\0');
	std::string noPaddingStr = "";
	if (nullPos != std::string::npos) {
		noPaddingStr = str.substr(0, nullPos);
	}
	return noPaddingStr;
}
