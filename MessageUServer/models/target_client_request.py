from models.base_request import Base_Request

class TargetClientRequest(Base_Request):
    def __init__(self, client_id, version, code, payload_size, payload):
        super().__init__(client_id, version, code, payload_size)
        self.payload = payload

    def __str__(self):
        if not self.client_id:
            return ""
        super_str = super().__str__()
        return f"{super_str}, payload={self.payload}"

    def get_payload(self):
        return self.payload
