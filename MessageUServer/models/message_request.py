from target_client_request import TargetClientRequest


class MessageRequest(TargetClientRequest):
    def __init__(self, client_id, version, code, payload_size, payload):
        super().__init__(client_id, version, code, payload_size, payload)

    def __str__(self):
        return f"Client ID: {self.client_id}, Version: {self.version}, Code: {self.code}, Payload Size: {self.payload_size}, Payload: {self.payload}"

    def process_request(self, client):
        pass
