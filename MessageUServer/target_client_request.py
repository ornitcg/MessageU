from base_request import BaseRequest

class TargetClientRequest(BaseRequest):
    def __init__(self, client_id, version, code, payload_size, payload):
        super().__init__(client_id, version, code, payload_size)
        self.payload = payload

    def __str__(self):
        return f"Client ID: {self.client_id}, Version: {self.version}, Code: {self.code}, Payload Size: {self.payload_size}, Payload: {self.payload}"
