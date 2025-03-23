#include <iostream>
#include "Connection.h"
#include "UImanager.h"
#include "RequestHandler.h"
#include "ResponseHandler.h"
#include "UserNameException.h"
#include "CurrentClient.h"


int main() {
	
	try {
		Connection conn = Connection();
		CurrentClient currentClient = CurrentClient();  // takes details from file if exists
		UImanager uiManager = UImanager();		
		RequestHandler requestHandler = RequestHandler(conn, currentClient, uiManager);
		ResponseHandler responseHandler = ResponseHandler(conn, currentClient , uiManager);
		
		while (true) {			
			try {
				uiManager.displayMenu();
				int choice = uiManager.getChoice();	// only valid choice accepted				
				if (static_cast<MenuOption>(choice) == MenuOption::EXIT)
					break;
				bool handled = requestHandler.handleChoice(choice);	
				if (handled) 
					responseHandler.receiveServerResponse(choice);
			}	
			catch (const UserNameException& e) {
				std::cout << e.what() << std::endl;
				conn.disconnect();
				break;
			}
			catch (const std::exception& e) {
				std::cout << e.what() << std::endl;							
			}
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;		
	}
	std::cout << "Exited client\n";	
	return 0;	
}