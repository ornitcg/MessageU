from models.base_response import Base_Response
from utils.defines import *
from utils.utils_funcs import *

class Register_Response(Base_Response):
    def __init__(self, binary_client_id , payload_size = CLIENT_ID_SIZE):
        super().__init__(Response_Code.REGISTER_SUCCEEDED.value[0], payload_size)
        self.binary_client_id = binary_client_id

    def get_binary_response(self):
        return self.get_binary_header() + self.binary_client_id

    # def __str__(self):
    #     if not self.binary_client_id:
    #         return ""
    #     super_str = super().__str__()
    #     return f"{super_str}, binary_client_id={self.binary_client_id}"



########## ******************************###########


class Users_List_Response(Register_Response):
    def __init__(self, client_id, binary_users_list, payload_size):
        super().__init__(  client_id, payload_size)
        self.binary_users_list = binary_users_list

    def get_binary_response(self):
        binary_header_and_client_id = super().get_binary_response()
        binary_response = binary_header_and_client_id + self.binary_users_list
        return binary_response

########## ******************************###########

class Public_Key_Response(Base_Response):
    def __init__(self, public_key):
        super().__init__(Response_Code.PUBLIC_KEY.value, len(public_key))
        self.public_key = public_key

    def get_binary_response(self):
        return self.get_binary_header() + self.public_key




########## ******************************###########


class Message_sent_response(Register_Response):
    def __init__(self,  code, payload_size , client_id , message_id):
        super().__init__( code, payload_size , client_id)
        self.message_id = message_id


    def get_binary_response(self):
        binary_header_and_client_id = super().get_binary_response()
        binary_message_id = self.message_id.encode()
        binary_response = binary_header_and_client_id + binary_message_id
        return binary_response


########## ******************************###########


class Message_sent_response(Message_sent_response):
    def __init__(self,  code, payload_size , client_id , message_id, message_type, message_size, content):
        super().__init__( code, payload_size , client_id, message_id)
        self.message_type = message_type
        self.message_size = message_size
        self.content = content

    def get_binary_response(self):
        binary_header_and_other = super().get_binary_response()
        binary_message_type = self.message_type.to_bytes(1, byteorder='little')
        binary_message_size = self.message_size.to_bytes(4, byteorder='little')
        binary_content = self.content.encode()
        binary_response = binary_header_and_other + binary_message_type + binary_message_size + binary_content
        return binary_response