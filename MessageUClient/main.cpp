#include <iostream>
#include "Connection.h"
#include "UImanager.h"
#include "RequestHandler.h"
#include "ResponseHandler.h"
#include "UserNameException.h"
#include "CurrentClient.h"
#include "EncryptionManager.h"
#include <filesystem>	
#include "utils.h"

int main() {
	
	try {
		CurrentClient currentClient;
		EncryptionManager encMngr = EncryptionManager();

		if (std::filesystem::exists(ME_INFO))
			currentClient = CurrentClient();  // takes details from file if exists
		else {
			currentClient = CurrentClient(encMngr.generateRSAKeys());  // generates new keys for new registration
		}

		Connection conn = Connection();		
		UImanager uiManager = UImanager();		
		RequestHandler requestHandler = RequestHandler(conn, currentClient, uiManager, encMngr);
		ResponseHandler responseHandler = ResponseHandler(conn, currentClient , uiManager, encMngr);
		
		while (true) {			
			try {
				uiManager.displayMenu();
				int choice = uiManager.getChoice();	// only valid choice accepted				
				if (static_cast<MenuOption>(choice) == MenuOption::EXIT)
					break;
				bool handled = requestHandler.handleChoice(choice);	
				if (handled) 
					responseHandler.receiveServerResponse(choice);
				
				//reconnection to make sure the connection is still alive			
				conn.disconnect();
				if (!conn.connectionInit()) {
					//throw ConnectionError("Failed to connect"); //TODO
					break;
				}				
			}	
			catch (const UserNameException& e) {
				std::cout << e.what() << std::endl;
				conn.disconnect();
				break;
			}
			/*catch (const ConnectionError& e) { //TODO
				throw e;
			}*/

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