from models.responses import Base_Response

class Register_Response(Base_Response):
    def __init__(self,  code, payload_size , client_id):
        super().__init__( code, payload_size)
        self.client_id = client_id


    def get_binary_response(self):
        binary_header = self.get_binary_header()
        binary_client_id = self.client_id.to_bytes(4, byteorder='little')
        binary_response = binary_header + binary_client_id
        return binary_response

########## ******************************###########


class Users_List_Response(Register_Response):
    def __init__(self,  code, payload_size , client_id , users_list):
        super().__init__( code, payload_size , client_id)
        self.users_list = users_list


    def get_binary_response(self):
        binary_header_and_client_id = super().get_binary_response()
        binary_users_list = self.users_list.encode()
        binary_response = binary_header_and_client_id + binary_users_list
        return binary_response

########## ******************************###########


class Public_key_response(Register_Response):
    def __init__(self,  code, payload_size , client_id , public_key):
        super().__init__( code, payload_size , client_id)
        self.public_key = public_key


    def get_binary_response(self):
        binary_header_and_client_id = super().get_binary_response()
        binary_public_key = self.public_key.encode()
        binary_response = binary_header_and_client_id + binary_public_key
        return binary_response


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