import datetime
from constants.defines import *
from base_request import BaseRequest


class Client:
    def __init__(self, socket, address):
        self.client_socket = socket
        self.address = address
        self.client_id = None
        self.user_name = None
        self.public_key = None
        self.inb = b''  # for incoming binary data
        self.outb = b''  # for outgoing binary data
        self.last_seen = None

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


    def extract_whole_request(self):
        if len(self.inb) < REQUEST_HEADER_SIZE:
            return None
        print(f"Request size: {len(self.inb)}") # TODO DEBUG
        self.client_id = self.inb[:CLIENT_ID_SIZE].decode()
        offset = CLIENT_ID_SIZE
        version = self.inb[offset:offset + VERSION_SIZE]
        offset += VERSION_SIZE
        code = self.inb[offset : offset + CODE_SIZE].decode()
        offset += CODE_SIZE
        # payload_size = self.inb[offset:offset + PAYLOAD_SIZE].decode()
        payload_size = int.from_bytes(self.inb[offset:offset + PAYLOAD_SIZE], byteorder='little')
        offset += PAYLOAD_SIZE
        print(f"Payload size: {payload_size}")
        payload = self.inb[offset:offset + payload_size]

        if payload == "":
            return BaseRequest(self.client_id, version , code, payload_size)
        else
