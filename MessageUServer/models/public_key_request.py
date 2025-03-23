from models.base_request import Base_Request
from utils.defines import *


class Public_Key_Request(Base_Request):
    def __init__(self, header, payload):
        super().__init__(request = header)
        self.target_client_id = payload[:CLIENT_ID_SIZE]


    def get_target_client_id(self):
        return self.target_client_id


