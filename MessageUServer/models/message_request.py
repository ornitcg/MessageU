from models.base_request import Base_Request
from utils.defines import *
from models.message import Message
from utils.server_messages import *


class Message_Request(Base_Request):
    def __init__(self, header, payload):
        super().__init__(request = header)
        if self.get_payload_size() > MAX_SIZE_4GB:
            raise ValueError("[ERROR] Payload size exceeds maximum payload size")
        self.parse_payload(payload)

    def parse_payload(self, payload):
        if len(payload) < CLIENT_ID_SIZE + MESSAGE_TYPE_SIZE + CONTENT_SIZE: #validate payload size
            raise ValueError(WRONG_PAYLOAD_SIZE_ERROR)
        self.target_client_id = payload[:CLIENT_ID_SIZE]
        if self.target_client_id == b'\x00' * CLIENT_ID_SIZE: #validate client id not empty
            raise ValueError("[ERROR] Invalid target client ID")
        if self.target_client_id == self.client_id: #validate client id not same as sender
            raise ValueError("[ERROR] Target client ID cannot be the same as sender client ID")

        offset = CLIENT_ID_SIZE
        self.message_type = int.from_bytes(payload[offset:offset+MESSAGE_TYPE_SIZE], byteorder='little')
        if self.message_type not in [mt.value for mt in Message_Type]: #validate message type
            raise ValueError(f"[ERROR] Invalid message type: {self.message_type}")

        offset += MESSAGE_TYPE_SIZE
        self.content_size = int.from_bytes(payload[offset:offset + CONTENT_SIZE],byteorder='little')
        offset += CONTENT_SIZE
        if len(payload) < offset + self.content_size:  #validate content size
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
