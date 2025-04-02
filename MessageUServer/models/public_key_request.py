from models.base_request import Base_Request
from utils.defines import *
from utils.server_messages import *


class Public_Key_Request(Base_Request):
    def __init__(self, header, payload):
        super().__init__(request = header)
        if len(payload) is not CLIENT_ID_SIZE:
            raise ValueError(WRONG_PAYLOAD_SIZE_ERROR)
        self.target_client_id = payload[:CLIENT_ID_SIZE]


    def get_target_client_id(self):
        return self.target_client_id


