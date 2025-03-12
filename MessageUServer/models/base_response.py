class BaseResponse:
    def __init__(self, version, code, payload_size = 0):
        self.version = version
        self.code = code
        self.payload_size = payload_size


    def get_binary_response(self):
        return f"{self.version}{self.code}{self.payload_size}".encode()
