#pragma once


//#define PORT 1357
#define MSG_SIZE 1024
//#define SERVER_IP "127.0.0.1"
#define SERVER_INFO "server.info"

std::array<std::string, 2> getServerIPfromFile(std::string fileName);
