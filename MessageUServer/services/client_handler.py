import datetime
import selectors
import uuid

from utils.defines import *
from services.request_handler import Request_Handler
from services.response_handler import Response_Handler


class Client_Handler:
    def __init__(self, socket, address, db_mngr, selector):
        self.client_socket = socket
        self.address = address
        self.db_mngr = db_mngr
        self.selector = selector
        self.inb = b''  # for incoming binary data
        self.outb = b''  # for outgoing binary data
        self.last_seen = None
        self.request_handler = Request_Handler(self, db_mngr)
        self.response_handler = Response_Handler(self, db_mngr)
        self.user_name = None
        self.client_id = None
        self.public_key = None
        self.clientList = []
        self.target_public_key = None
        self.is_request_successful = False
        self.message_id = None
        self.request_object = None
        self.response_object = None

    def set_client_with_request_object(self, request):
        self.client_id = request.get_client_id()

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
            is_request_processed = False #initialize to false
            self.is_request_successful = False #initialize to false
            if mask & selectors.EVENT_READ:
                    is_request_processed = self.handle_read_event()
            if self.outb and (mask & selectors.EVENT_WRITE) :
                    self.handle_write_event()
                    if not self.outb:
                        self.selector.modify(key.fileobj, selectors.EVENT_READ, data=self)
            return is_request_processed
        except Exception as e:
            print(f"[ERROR] Error handling client in handle event {self.address}: {e}")
            self.response_handler.send_error_response()
            return False  # Signal that this client has been handled


    def handle_read_event(self):
        try:
            recv_data = self.client_socket.recv(MAX_BUFFER_SIZE)
            print(f"[LOG] Received data from client {self.address}: {recv_data}")  # TODO
            if not recv_data:
                print(f"[LOG] Client {self.address} disconnected")
                raise ConnectionError("Client disconnected")

            if self.client_id: #case client already registered
                self.db_mngr.update_client_last_seen(self.client_id)
            self.add_to_receive_buf(recv_data)

            total_request_size = self.request_handler.is_extract_complete_request(self.inb)
            if total_request_size: #if not None then it's complete
                self.request_object = self.request_handler.get_request_object(self.inb)
                self.remove_processed_data_from_inb(total_request_size)
                self.is_request_successful = self.request_handler.handle_request(self.request_object)
            return True
        except (ConnectionError, ConnectionResetError, BrokenPipeError) as e:
            print(f"[LOG] Response sent, client {self.address} disconnected")
            self.disconnect_client()
        except Exception as e:
            print (f"[ERROR] Error in handling client {self.address}: {e} " )
            raise e


    def handle_write_event(self):
        try:
            sent = self.client_socket.send(self.get_final_send_data())
            if sent == 0:
                print(f"[ERROR] Failed to send data to client {self.address}")

        except (ConnectionError, ConnectionResetError, BrokenPipeError) as e:
            print(f"[ERROR] Connection error with client {self.address}")
            raise e
        except Exception as e:
            print(f"[ERROR] Error in handling client {self.address}: {e} ")
            raise e


    def generate_client_id(self):
        new_uuid = uuid.uuid4()
        self.client_id = new_uuid

    def get_binary_client_id(self):
        if not self.client_id:
            return None
        return self.client_id.bytes

    def remove_processed_data_from_inb(self, total_request_size):
        self.inb = self.inb[total_request_size+1:]  # remove the processed data


    def update_client_with_request_payload(self, request):
        self.user_name = request.user_name
        self.public_key = request.public_key


    def get_client_id(self):
        return self.client_id

    def set_client_id(self, id):
        if not self.client_id:
            self.client_id = id
        else:
            raise Exception("[ERROR] Client ID already set")

    def get_user_name(self):
        return self.user_name

    def get_public_key(self):
        return self.public_key

    def get_parsed_request(self):
        return self.request_object

    def get_is_request_success(self):
        return self.is_request_successful

    def disconnect_client(self):
        try:
            self.client_socket.close()
            self.selector.unregister(self.client_socket)
            return
        except Exception as cleanup_error:
            print(f"[ERROR] Error during client cleanup: {cleanup_error}")



    def set_client_list(self, list):
        self.clientList = list

    def get_client_list(self):
        return self.clientList


    def set_target_public_key(self, key):
        self.target_public_key = key

    def get_target_public_key(self):
        return self.target_public_key

    def set_target_client_id(self, client_id):
        self.target_client_id = client_id

    def get_target_client_id(self):
        return self.target_client_id


    def set_message_id(self, msg_id):
        self.message_id = msg_id

    def get_message_id(self):
        return self.message_id

    def get_request_object(self):
        return self.request_object