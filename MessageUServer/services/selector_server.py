import socket
import selectors
from services.client_handler import Client_Handler
from utils.defines import MAX_CONNECTIONS, MAX_BUFFER_SIZE
from data.database_manager import Database_Manager


'''Manages the selector and event loop for the server
Accpts new connections
Dispatch events to the appropriate ClientHandler'''

class SelectorServer:
    def __init__(self,  host, port):
        self.host = host
        self.port = port
        self.selector = selectors.DefaultSelector()
        self.server_socket = None
        self.db_mngr = Database_Manager()
        self.db_conn = self.db_mngr.initialize_db()


        if not self.db_conn:
            raise Exception("[ERROR] Failed to initialize the database")

    def connect(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.setblocking(False)  # non-blocking mode
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(MAX_CONNECTIONS)
        print(f"[LOG] Server is listening on port {self.port}")
        self.selector.register(self.server_socket, selectors.EVENT_READ , data=None)
        self.event_loop()


    def event_loop(self):
        try:
            while True:
                events = self.selector.select(timeout=None)
                for key, mask in events:
                    if key.data is None:
                        self.accept_connection(self.server_socket)
                    else:
                        client_handler = key.data
                        try:
                            request_processed = client_handler.handle_event(key, mask)
                            if request_processed and client_handler.get_is_request_success():
                                client_handler.response_handler.handle_response(client_handler.get_parsed_request(),
                                                                                client_handler.get_is_request_success)


                        except Exception as e:
                            print(f"[ERROR] Error handling client in event loop {client_handler.address}: {e}")
                            client_handler.response_handler.send_error_response()
                            print("[LOG] error response sent from event loop")

        except KeyboardInterrupt:
            print("[ERROR] KeyboardInterrupt Server is shutting down")
        except Exception as e:
            print(f"[ERROR] Error in event loop: {e}")
        finally:
            self.close()

    def accept_connection(self, sock):
        # Accept the connection
        client_socket, addr = sock.accept()
        print(f"[LOG] Accepted connection from {addr}")
        client_socket.setblocking(False)
        client_handler = Client_Handler(client_socket, addr, self.db_mngr, self.selector)
        client_handler.update_last_seen()
        events = selectors.EVENT_READ | selectors.EVENT_WRITE
        self.selector.register(client_socket, events, data=client_handler)
        return client_handler

    def close(self):
        print("[LOG] Closing server")
        self.db_mngr.disconnect()
        self.selector.close()
        if self.server_socket:
            self.server_socket.close()