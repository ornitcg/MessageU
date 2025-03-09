#pragma once
#include <array>
#include <string>

#define MSG_SIZE 1024
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define SERVER_INFO "server.info"
#define ME_INFO "me.info"
#define SERVER_VERSION 2
#define MAX_NAME_SIZE 254
#define CLIENT_ID_SIZE 16

std::array<std::string, 2> getServerIPfromFile(std::string fileName);
