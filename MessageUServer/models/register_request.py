from models.base_request import Base_Request
from utils.defines import *

class Register_Request(Base_Request):
    def __init__(self, header, payload):
        super().__init__(request = header)
        self.user_name = None
        self.public_key = None
        self.parse_payload(payload)

    def parse_payload(self, payload):
        user_name_bytes = payload[:USER_NAME_SIZE]
        null_pos = user_name_bytes.find(b'\x00')
        if null_pos != -1:
            self.user_name = user_name_bytes[:null_pos].decode('utf-8',errors='ignore')
        else:
            self.user_name = user_name_bytes.decode('utf-8',errors='ignore')

        offset = USER_NAME_SIZE
        self.public_key = payload[offset : offset + PUBLIC_KEY_SIZE]




