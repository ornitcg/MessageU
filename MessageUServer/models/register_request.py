from models.base_request import Base_Request
from utils.defines import *
from utils.server_messages import *

class Register_Request(Base_Request):
    def __init__(self, header, payload):
        super().__init__(request = header)
        self.user_name = None
        self.public_key = None
        self.parse_payload(payload)

    def parse_payload(self, payload):
        if len(payload) < USER_NAME_SIZE + PUBLIC_KEY_SIZE:
            raise ValueError(WRONG_PAYLOAD_SIZE_ERROR)
        user_name_bytes = payload[:USER_NAME_SIZE]
        null_pos = user_name_bytes.find(b'\x00')
        if null_pos != -1:
            self.user_name = user_name_bytes[:null_pos].decode('ascii',errors='strict')
        else:
            self.user_name = user_name_bytes.decode('ascii',errors='strict')

        offset = USER_NAME_SIZE
        self.public_key = payload[offset : offset + PUBLIC_KEY_SIZE]




