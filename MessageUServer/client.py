import datetime
from constants.defaults import *



class Client:
    def __init__(self, socket, address):
        self.client_socket = socket
        self.address = address
        self.client_id = None
        self.name = None
        self.pub_key = None
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

    def process_data(self, recv_data):
        print(f"Processing data from {self.address}")
        self.add_to_receive_buf(recv_data)
        print(self.inb.decode()) ## TODO DEBUG
        self.clear_receive_buffer()
        pass
