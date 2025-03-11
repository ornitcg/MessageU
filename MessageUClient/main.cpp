#include <iostream>
#include "Connection.h"
#include "UImanager.h"
#include "RequestHandler.h"
#include "ResponseHandler.h"


int main() {
	
	try {
		Connection conn = Connection();
		Client client = Client(conn);
		UImanager uiManager = UImanager();		
		RequestHandler requestHandler = RequestHandler(client, uiManager);
		ResponseHandler responseHandler = ResponseHandler(client, uiManager);
		
		while (true) {			
			try {
				uiManager.displayMenu();
				int choice = uiManager.getChoice();	// only valid choice accepted				
				requestHandler.handleChoice(choice);	
				responseHandler.handleServerResponse();
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