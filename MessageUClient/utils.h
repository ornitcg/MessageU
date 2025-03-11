#pragma once
#include <array>
#include <string>

#define MSG_SIZE 1024
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


#define REGISTER_REQUEST_PAYLOAD_SIZE MAX_NAME_SIZE + PUBLIC_KEY_SIZE + 1 



std::array<std::string, 2> getServerIPfromFile(std::string fileName);
