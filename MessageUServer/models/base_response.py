from utils.defines import *
import struct

class Base_Response:
    def __init__(self, code, payload_size = 0):
        self.version = SERVER_VERSION
        self.code = code
        self.payload_size = payload_size

    def get_binary_header(self):
        print(f"in get_binary_header Version: {self.version}, Code: {self.code}, Payload Size: {self.payload_size}")
        return struct.pack('<BHI', self.version, self.code, self.payload_size)

    def get_binary_response(self):
       return self.get_binary_header()




class Error_Response(Base_Response):
    def __init__(self, code = Response_Code.GENERAL_ERROR.value):
        super().__init__(code)






