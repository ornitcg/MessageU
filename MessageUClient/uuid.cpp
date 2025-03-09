#include "uuid.h"
#include <string>
#include <iostream>

myUUID::myUUID() {}

myUUID::~myUUID() {
}

std::array<uint8_t, 16> myUUID::getUUID()
{
	return uuid;
}

std::string myUUID::getBinary() const//not LE yet DEBUG TODO
{
	//std::string uuidString = "";
	//for (int i = 0; i < 16; i++) {
	//	uuidString += uuid[i];
	//}
	//std::cout << "uuidString: " << uuidString << std::endl; //DEBUG
	//return uuidString;
	return std::string(reinterpret_cast<const char*>(uuid.data()), 16);
}


void myUUID::setUUID(const void* binaryData) {
	memcpy(uuid.data(), binaryData, 16);
}
