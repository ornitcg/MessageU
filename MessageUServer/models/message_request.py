from models.base_request import Base_Request
from utils.defines import *
from models.message import Message
from utils.server_messages import *

class Message_Request(Base_Request):
    def __init__(self, header, payload):
        super().__init__(request = header)
        self.parse_payload(payload)

    def parse_payload(self, payload):
        if len(payload) < CLIENT_ID_SIZE + MESSAGE_TYPE_SIZE + CONTENT_SIZE:
            raise ValueError(WRONG_PAYLOAD_SIZE_ERROR)
        self.target_client_id = payload[:CLIENT_ID_SIZE]
        offset = CLIENT_ID_SIZE
        self.message_type = int.from_bytes(payload[offset:offset+MESSAGE_TYPE_SIZE], byteorder='little')
        offset += MESSAGE_TYPE_SIZE
        self.content_size = int.from_bytes(payload[offset:offset + CONTENT_SIZE],byteorder='little')
        offset += CONTENT_SIZE
        if len(payload) < offset + self.content_size:
            raise ValueError("[ERROR] Content size exceeds payload length")
        self.content = payload[offset:offset + self.content_size]

    def get_message(self):
        return Message(self.get_target_client_id(), self.get_client_id(), self.get_message_type(), self.get_content())

    #getters
    def get_target_client_id(self):
        return self.target_client_id
    def get_message_type(self):
        return self.message_type
    def get_content(self):
        return self.content

    def __str__(self):
        return f"Message_Request(to client_id={self.target_client_id}, message_type={self.message_type}, content={self.content})"
