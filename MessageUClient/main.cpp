//include winsock for client
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <WinSock2.h>   //must be first
#include <windows.h>    //must be second
#pragma comment(lib, "ws2_32.lib") 
#define PORT 1357
#define MSG_SIZE 1024
#define SERVER_IP "127.0.0.1"


int main() {
	std::cout << "Im OK" << std::endl;
	WSADATA wsaData;
	int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);

	//socket
	SOCKET clientSocket;

	if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) // AF_INET = IPv4, SOCK_STREAM = TCP specific type of socket , IPPROTO_TCP = TCP
	{
		std::cout << "Client socket creation error" << std::endl;
		return -1;
	}

	//connect
	struct sockaddr_in serverAddr = { 0 }; // struct that holds the server address
	serverAddr.sin_family = AF_INET; // IPv4
	serverAddr.sin_port = htons(PORT); // turns the endianess of the port to network endianess
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP); // server address is any address
	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));


	//send
	send(clientSocket, "Hello from cpp client!", 22, 0);
	std::cout << "Message sent to server" << std::endl;


	//recv
	std::cout << "Message from server:" << std::endl;
	char servermsg[MSG_SIZE] = { 0 };
	recv(clientSocket, servermsg, MSG_SIZE, 0);
	std::cout << servermsg << std::endl;


	//close
	closesocket(clientSocket);


	//cleanup
	WSACleanup();
	system("pause");
	return 0;



	
}