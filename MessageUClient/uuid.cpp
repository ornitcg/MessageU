#include "uuid.h"
#include <string>
#include <iostream>

myUUID::myUUID() {
	//initiallize uuidArray to 16 of 0
	for (auto& i : uuidArray)
	{
		i = '0';
	}
}

myUUID::~myUUID() {
}

std::array<uint8_t, 16>& myUUID::getUUID() 
{
	return uuidArray;
}

std::string myUUID::getBinary() //not LE yet DEBUG TODO
{
	return std::string(uuidArray.begin(), uuidArray.end());
}



void myUUID::setUUID(const void* binaryData) {
	memcpy(uuidArray.data(), binaryData, 16);
}
