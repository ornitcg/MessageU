from base_response import BaseResponse

class RegisterResponse(BaseResponse):
    def __init__(self, version, code, payload_size , client_id):
        super().__init__(version, code, payload_size)
        self.client_id = client_id


    def get_binary_response(self):
        return f"{self.version}{self.code}{self.payload_size}{self.client_id}".encode()