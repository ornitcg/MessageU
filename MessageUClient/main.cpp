//include winsock for client
#include "connection.h"
#include "client.h"
#include <iostream>
#include "RequestInfo.h"



int main() {
	try {
		Connection conn;
		SOCKET client_socket = conn.getClientSocket();
		std::cout << "Client socket: " << client_socket << std::endl;
		if (client_socket < 0) {
			std::cout << "Client socket creation error" << std::endl;
			return 1;
		}

		Client client(client_socket);
		int choice = 1;

		while (choice) {
			displayMenu();
			try {
				choice = client.getChoice();	// only valid accepted
				client.handleChoice(static_cast<MenuOption> (choice));
				
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;
				choice = 1; // to keep the loop going
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "Exited client\n";

	////send
	//send(clientSocket, "Hello from cpp client!", 22, 0);
	//std::cout << "Message sent to server" << std::endl;


	////recv
	//std::cout << "Message from server:" << std::endl;
	//char servermsg[MSG_SIZE] = { 0 };
	//recv(clientSocket, servermsg, MSG_SIZE, 0);
	//std::cout << servermsg << std::endl;

	

	/*system("pause");*/
	return 0;	
}