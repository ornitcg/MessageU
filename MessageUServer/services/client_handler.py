import datetime
import selectors

from utils.defines import *
from models.base_request import BaseRequest
from services.request_handler import RequestHandler
from services.response_handler import ResponseHandler


# Handles the communication for a specific client


class Client_Handler:
    def __init__(self, socket, address, db_conn, db_mngr):
        self.client_socket = socket
        self.address = address
        self.client_id = None
        self.user_name = None
        self.public_key = None
        self.inb = b''  # for incoming binary data
        self.outb = b''  # for outgoing binary data
        self.last_seen = None
        self.request_handler = RequestHandler(self, db_conn, db_mngr)
        self.response_handler = ResponseHandler(self, db_conn, db_mngr)


    def add_to_send_buf(self, data):
        self.outb += data

    def add_to_receive_buf(self, data):
        self.inb += data

    def clear_receive_buffer(self):
        self.inb = b''

    def get_final_send_data(self ):
        if not self.outb:
            return b''
        data = self.outb[:MAX_BUFFER_SIZE]
        self.outb = self.outb[MAX_BUFFER_SIZE:]
        return data

    def update_last_seen(self):
        self.last_seen = datetime.datetime.now()

    def handle_event(self, key, mask):
        try:
            if mask & selectors.EVENT_READ:
                    self.handle_read()
            if mask & selectors.EVENT_WRITE and key.data.outb:
                    self.handle_write()
        except Exception as e:
            print(f"Error handling client {self.address}: {e}")
            raise e



    def handle_read(self):
        try:
            print("in handle_read") # TODO DEBUG
            recv_data = self.client_socket.recv(MAX_BUFFER_SIZE)
            if recv_data:
                if self.client_id:
                    self.db_mngr.update_client_last_seen(self.client_id)
                self.add_to_receive_buf(recv_data)
                while True:
                    is_request_complete = self.request_handler.is_extract_complete_request(self.inb)
                    if not is_request_complete:
                        break  # and move on to the next incoming data

                    parsed_request = self.request_handler.parse_request(self.inb)
                    response = self.request_handler.handle_request(parsed_request)
                    print(f"Request: {parsed_request}")  # TODO DEBUG

                    if response:
                        self.add_to_send_buf(response)
            else:  # case of empty data meaning client disconnected
                print(f"Client {self.address} disconnected")
                self.selector.unregister(self.client_socket)
                self.client_socket.close()
        except (ConnectionError, ConnectionResetError, BrokenPipeError) as e:
            print(f"Connection error with client {self.address}")
            raise e
        except Exception as e:
            print (f"Error in handling client {self.address}: {e} " )
            raise e


    def handle_write(self):
        try:
            sent = self.client_socket.send(self.get_final_send_data())
            if sent == 0:
                print(f"Failed to send data to client {self.address}")
                self.selector.unregister(self.client_socket)
                self.client_socket.close()
        except (ConnectionError, ConnectionResetError, BrokenPipeError) as e:
            print(f"Connection error with client {self.address}")
            self.selector.unregister(self.client_socket)
            self.client_socket.close()
        except Exception as e:
            print(f"Error in handling client {self.address}: {e} ")
            self.selector.unregister(self.client_socket)
            self.client_socket.close()





