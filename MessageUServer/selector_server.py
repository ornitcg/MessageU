import socket
import selectors
from client import Client
from constants.messages import *



class SelectorServer:
    def __init__(self,  port):
        self.host = ''
        self.port = port
        self.selector = selectors.DefaultSelector()
        self.server_socket = None


    def connect(self):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.setblocking(False)  # non-blocking mode
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(MAX_CONNECTIONS)
        print(f"Server is listening on port {self.port}")
        self.selector.register(self.server_socket, selectors.EVENT_READ, data=None)
        self.event_loop()


    def event_loop(self):
        try:
            print("Server is running")
            while True:
                events = self.selector.select(timeout=None)
                for key, mask in events:
                    if key.data is None:
                        self.accept(key.fileobj)
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
        self.sel.register(client_socket, events, data=client)\

        print(f"Client from {addr} registered with selector")  ## TODO DEBUG



    def send(self, data):
        self.send(data)

    def recv(self, size):
        return self.recv(size)

    def close(self):
        self.close()