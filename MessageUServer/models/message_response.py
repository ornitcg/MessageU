from utils.defines import *
from models.base_response import Base_Response
import struct


class Message_Response(Base_Response):
    def __init__(self, msg_id, target_client_id):
        super().__init__(code = Response_Code.MESSAGE_SENT.value[0] , payload_size = CLIENT_ID_SIZE + MESSAGE_ID_SIZE )
        self.msg_id = msg_id
        self.target_client_id = target_client_id


    def get_binary_response(self):
        binary_header = self.get_binary_header()
        binary_msg_id = struct.pack('<I', self.msg_id)
        binary_target_client_id = self.target_client_id
        binary_response = binary_header +  binary_target_client_id + binary_msg_id
        print("binary_response: ", binary_response)
        #print size
        print("binary_response size: ", len(binary_response))
        return binary_response