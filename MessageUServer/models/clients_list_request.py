from models.base_request import Base_Request



class Clients_List_Request(Base_Request):
    def __init__(self, header):
        super().__init__(request = header)

