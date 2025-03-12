from models.base_request import BaseRequest
from utils.defines import *

class RegisterRequest(BaseRequest):
    def __init__(self, client_id, version, code, payload_size, payload):
        super().__init__(client_id, version, code, payload_size)
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
        self.public_key = payload[USER_NAME_SIZE:USER_NAME_SIZE+PUBLIC_KEY_SIZE]

    def __str__(self):
        return f"Client ID: {self.client_id}, Name: {self.name}, Public Key: {self.pub_key}"

