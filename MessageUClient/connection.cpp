#include <array>
#include "connection.h"
#include "utils.h"
#include <ws2tcpip.h> 

Connection::Connection()
{
	clientSocket = -1;
	if (!connectionInit()) {
		throw std::runtime_error("Failed to initiallize connection! ");
	}
}

Connection::~Connection()
{
	if (clientSocket != 0) {
		closesocket(clientSocket);
	}
	WSACleanup();
}

SOCKET Connection::getClientSocket()
{
	return clientSocket;
}

bool Connection::connectionInit()
{
	try {
		WSADATA wsaData;
		int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (ret != 0)
		{
			throw std::runtime_error("WSAStartup failed");
		}

		//socket
		if ((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) // AF_INET = IPv4, SOCK_STREAM = TCP specific type of socket , IPPROTO_TCP = TCP
		{
			throw std::runtime_error("Client socket creation error");
		}

		//connect
		std::array<std::string, 2 > serverInfo = getServerIPfromFile(SERVER_INFO);
		std::string serverIp = serverInfo[0];
		int port = std::stoi(serverInfo[1]);
		
		//std::cout << "Connecting to server " << serverIp << " on port " << port << std::endl;	// TODO DEBUG
		struct sockaddr_in serverAddr = { 0 }; // struct that holds the server address
		serverAddr.sin_family = AF_INET; // IPv4
		serverAddr.sin_port = htons(port); // turns the endianess of the port to network endianess
		
		if (inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr) <= 0) {
			throw std::runtime_error("Invalid address/ Address not supported");
		}

		if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
		{
			throw std::runtime_error("Connection to server failed");
		}
		return true;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	}
}
