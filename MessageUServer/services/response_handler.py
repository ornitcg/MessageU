from  models.responses import *
from utils.defines import *

class Response_Handler:
    def __init__(self, client_handler, db_conn, db_mngr):
        self.client_handler = client_handler
        self.db_conn = db_conn
        self.db_mngr = db_mngr

    def create_binary_error_response(self):
        error_response = Error_Response(code = Response_Code.GENERAL_ERROR.value)
        binary_error_response = error_response.get_binary_response()
        return binary_error_response

    def create_binary_register_response(self, client_id):
        response = _(SERVER_VERSION, Response_Code.REGISTER_SUCCEEDED.value, 0, client_id)
        binary_response = response.get_binary_response()
        return binary_response