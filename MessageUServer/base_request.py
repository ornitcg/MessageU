from constants.defines import *

class BaseRequest:
    def __init__(self, client_id, version, code, payload_size):
        self.client_id = client_id
        self.version = version
        self.code = code
        self.payload_size = payload_size



    def __str__(self):
        return f"URL: {self.url}, Method: {self.method}, Headers: {self.headers}, Body: {self.body}"


