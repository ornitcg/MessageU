from models.base_request import BaseRequest
from utils.defines import *

class RegisterRequest(BaseRequest):
    def __init__(self, client_id, version, code, payload_size, payload):
        super().__init__(client_id, version, code, payload_size)
        self.user_name = None
        self.pub_key = None
        self.parse_payload(payload)

    def parse_payload(self, payload):
        self.user_name = payload[:USER_NAME_SIZE].decode().strip()
        self.public_key = payload[USER_NAME_SIZE:].decode().strip()

    def __str__(self):
        return f"Client ID: {self.client_id}, Name: {self.name}, Public Key: {self.pub_key}"

