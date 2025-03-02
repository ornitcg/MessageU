import datetime


class Client:
    def __init__(self, socket, address):
        self.client_socket = socket
        self.address = address
        self.client_id = None
        self.name = None
        self.pub_key = None
        self.inb = b''
        self.outb = b''
        self.last_seen =None


    def add_to_send_buf(self, data):
        self.outb += data

    def add_to_receive_buf(self, data):
        self.inb += data


    def clear_recv_buffer(self):
        self.inb = b''



    def get_final_send_data(self, max_size=4096):
        if not self.outb:
            return b''
        data = self.outb[:max_size]
        self.outb = self.outb[max_size:]
        return data

    def update_last_seen(self):
        self.last_seen = datetime.datetime.now()


    def process_data(self):
        print(f"Processing data from {self.address}")
        self.add_to_send_buffer(self.inb)
        self.clear_recv_buffer()
        pass