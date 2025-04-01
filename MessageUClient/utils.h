#pragma once
#include <array>
#include <string>
#include "defines.h"






//*********** formatting *******************

std::string toLittleEndian32string(uint32_t value);

uint32_t toLittleEndian32(uint32_t value);

std::string toLittleEndian16string(uint16_t value);

uint16_t toLittleEndian16(uint16_t value);

bool isLittleEndian();

std::string trimNonPrintableChars(const std::string& str);

std::string removeZeroPadding(const std::string& str);

// *********** used for debugging ***************
void printAsHex(const std::string& binaryData);


//*********** file handling *****************

std::array<std::string, 2> getServerIPfromFile(std::string fileName);

std::string readFileData(std::string& filePath);

std::string generateRandomFileName();

std::string writeFileData(const std::string& content);

std::string getTempDirectory();


