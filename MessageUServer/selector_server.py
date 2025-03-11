import socket
import selectors
from client import Client
from constants.server_messages import *
from constants.defines import MAX_CONNECTIONS, MAX_BUFFER_SIZE
from database_manager import DatabaseManager
from request_handler import RequestHandler


class SelectorServer:
    def __init__(self,  host, port):
        self.host = host
        self.port = port
        self.selector = selectors.DefaultSelector()
        self.server_socket = None
        self.db_mngr = DatabaseManager()
        self.db_conn = self.db_mngr.initialize_db()
        self.request_handler = RequestHandler(self.db_conn)

        if not self.db_conn:
            print("Failed to initialize the database")
            raise Exception("Failed to initialize the database")

    def connect(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.setblocking(False)  # non-blocking mode
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(MAX_CONNECTIONS)
        print(f"Server is listening on port {self.port}")
        self.selector.register(self.server_socket, selectors.EVENT_READ , data=None)
        self.event_loop()


    def event_loop(self):
        try:
            print("Server is running")
            while True:
                events = self.selector.select(timeout=None)
                for key, mask in events:
                    if key.data is None:
                        self.accept_connection(self.server_socket)
                    else:
                        self.handle_client(key, mask)
        except KeyboardInterrupt:
            print("Server is shutting down")
        finally:
            self.close()

    def accept_connection(self, sock):
        # Accept the connection
        client_socket, addr = sock.accept()
        print(f"Accepted connection from {addr}")
        client_socket.setblocking(False)
        client = Client(client_socket, addr)
        client.update_last_seen()
        events = selectors.EVENT_READ | selectors.EVENT_WRITE
        self.selector.register(client_socket, events, data=client)
        print(f"Client from {addr} registered with selector")  ## TODO DEBUG


    def handle_read(self, client):
        try:
            recv_data = client.client_socket.recv(MAX_BUFFER_SIZE)
            if recv_data:
                if client.client_id:
                    self.db_mngr.update_client_last_seen(client.client_id)
                client.add_to_receive_buf(recv_data)
                while True:
                    request = client.extract_whole_request()
                    if not request:
                        break  # and move on to the next incoming data

                    response = self.request_handler.perform_request(client, request, self.db_conn)
                    if response:
                        client.add_to_send_buf(response)
            else:  # case of empty data meaning client disconnected
                print(f"Client {client.address} disconnected")
                self.selector.unregister(client.client_socket)
                client.client_socket.close()
        except (ConnectionError, ConnectionResetError, BrokenPipeError) as e:
            print(f"Connection error with client {client.address}")
            self.selector.unregister(client.client_socket)
            client.client_socket.close()
        except Exception as e:
            print (f"Error in handling client {client.address}: {e} " )
            self.selector.unregister(client.client_socket)
            client.client_socket.close()


    def handle_write(self, client):
        try:
            sent = client.client_socket.send(client.get_final_send_data())
            if sent == 0:
                print(f"Failed to send data to client {client.address}")
                self.selector.unregister(client.client_socket)
                client.client_socket.close()
        except (ConnectionError, ConnectionResetError, BrokenPipeError) as e:
            print(f"Connection error with client {client.address}")
            self.selector.unregister(client.client_socket)
            client.client_socket.close()
        except Exception as e:
            print(f"Error in handling client {client.address}: {e} ")
            self.selector.unregister(client.client_socket)
            client.client_socket.close()


    def handle_client(self, key, mask):
        client = key.data
        try:
            if mask & selectors.EVENT_READ:
                    self.handle_read(client)
            if mask & selectors.EVENT_WRITE and client.outb:
                    self.handle_write(client)
        except ConnectionError:
            print(f"Connection error with client {client.address}")
            self.selector.unregister(client.client_socket)
            client.client_socket.close()

    def close(self):
        print("Closing server")
        self.db_mngr.disconnect()
        self.selector.close()
        if self.server_socket:
            self.server_socket.close()