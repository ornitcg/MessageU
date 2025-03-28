#pragma once
#include <array>
#include <string>

#define MSG_SIZE 1024
#define RESPONSE_HEADER_SIZE 7
#define MAX_BUFF MSG_SIZE 
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define SERVER_INFO "server.info"
#define ME_INFO "me.info"
#define SERVER_VERSION_SIZE 1
#define SERVER_VERSION 2
#define CLIENT_VERSION_SIZE 1
#define CLIENT_VERSION 2
#define MAX_NAME_SIZE 254
#define PUBLIC_KEY_SIZE 160
#define CLIENT_ID_SIZE 16
#define RESPONSE_CODE_SIZE 2
#define RESPONSE_PAYLOAD_SIZE 4
#define NO_PAYLOAD 0
#define NO_CONTENT 0
#define EMPTY_CONTENT ""
#define SYM_KEY_SIZE 16 // 16 bytes = 128 bits
#define MESSAGE_TYPE_FIELD_SIZE 1
#define CONTENT_SIZE_FIELD_SIZE 4
#define MESSAGE_ID_SIZE 4
#define SEND_MESSAGE_HEADER_SIZE  CLIENT_ID_SIZE + MESSAGE_TYPE_FIELD_SIZE + CONTENT_SIZE_FIELD_SIZE
#define RECV_MESSAGE_HEADER_SIZE  CLIENT_ID_SIZE + MESSAGE_ID_SIZE + MESSAGE_TYPE_FIELD_SIZE + CONTENT_SIZE_FIELD_SIZE

#define GET_SYM_KEY_MSG "Request for symmetric key"
#define RECV_SYM_KEY_MSG "Symmetric key received"
#define ERROR_TEXT_MSG "Can't decrypt message"
#define UNKNOWN_USER "Unknown user"
#define MESSAGE_DISPLAY_ERROR "Can't decrypt message!"


#define REGISTER_REQUEST_PAYLOAD_SIZE MAX_NAME_SIZE + PUBLIC_KEY_SIZE + 1 



std::array<std::string, 2> getServerIPfromFile(std::string fileName);
std::string toLittleEndian32string(uint32_t value);
uint32_t toLittleEndian32(uint32_t value);
std::string toLittleEndian16string(uint16_t value);
uint16_t toLittleEndian16(uint16_t value);
//void printAsHex(const std::string& binaryData);
bool isLittleEndian();
std::string trimNonPrintableChars(const std::string& str);
std::string removeZeroPadding(const std::string& str);