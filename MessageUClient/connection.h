#pragma once
#include <iostream>
#include <string>
#include <WinSock2.h>   //must be first
#include <windows.h>    //must be second
#pragma comment(lib, "ws2_32.lib") 


class Connection{
private:
	SOCKET clientSocket;


public:
	Connection();
	~Connection();
	SOCKET getClientSocket() const;
	void disconnect();
	bool connectionInit();
};

