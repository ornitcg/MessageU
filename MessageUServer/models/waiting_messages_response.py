from models.base_response import Base_Response
from utils.defines import *


class Waiting_Messages_Response(Base_Response):
    def __init__(self, list_payload):
        super().__init__(code = Response_Code.WAITING_MESSAGES.value[0])
        self.binary_messages_list = self.get_binary_payload(list_payload)
        self.payload_size = len(self.binary_messages_list)

    def get_binary_payload(self, list_payload):
        binary_messages_payload = b""
        for message in list_payload:
            binary_messages_payload += message.get_binary_message()
        return binary_messages_payload

    def get_binary_response(self):
        binary_header = super().get_binary_response()
        binary_response = binary_header + self.binary_messages_list
        return binary_response