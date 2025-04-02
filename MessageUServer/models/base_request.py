class Base_Request:
    def __init__(self, client_id = None, version= None, code= None, payload_size= None, request = None):
        if request:
            self.client_id = request.get_client_id()
            self.version = request.get_version()
            self.code = request.get_code()
            self.payload_size = request.get_payload_size()
        else: #be copy constructor
            self.client_id = client_id
            self.version = version
            self.code = code
            self.payload_size = payload_size



    def get_client_id(self):
        return self.client_id
    def get_version(self):
        return self.version
    def get_code(self):
        return self.code
    def get_payload_size(self):
        return self.payload_size