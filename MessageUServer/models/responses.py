from utils.defines import *

class Base_Response:
    def __init__(self, code, payload_size = 0):
        self.version = SERVER_VERSION
        self.code = code
        self.payload_size = payload_size

    def get_binary_header(self):
        binary_version = self.version.to_bytes(1, byteorder='little')
        binary_code = self.code.to_bytes(2, byteorder='little')
        binary_payload_size = self.payload_size.to_bytes(4, byteorder='little')
        return binary_version + binary_code + binary_payload_size


    def get_binary_response(self):
       return self.get_binary_header()


class Error_Response(Base_Response):
    def __init__(self):
        super().__init__(Response_Code.GENERAL_ERROR.value)

