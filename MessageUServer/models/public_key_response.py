from models.base_response import Base_Response
from utils.defines import *



class Public_Key_Response(Base_Response):
    def __init__(self, target_client_id, target_public_key):
        super().__init__(Response_Code.PUBLIC_KEY.value[0], PUBLIC_KEY_SIZE)
        self.target_client_id = target_client_id
        self.target_public_key = target_public_key[0]


    def get_binary_response(self):
        return  self.get_binary_header() + self.target_client_id + self.target_public_key


