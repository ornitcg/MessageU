from  models.base_response import *
from utils.defines import *
from models.register_response import Register_Response




class Response_Handler:
    def __init__(self, client_handler, db_mngr):
        self.client_handler = client_handler
        self.db_mngr = db_mngr

    def create_binary_error_response(self):
        error_response = Error_Response(code = Response_Code.GENERAL_ERROR.value)
        binary_error_response = error_response.get_binary_response()
        return binary_error_response

    def create_binary_register_response(self):
        binary_client_id = self.client_handler.get_binary_client_id()
        response = Register_Response(binary_client_id)
        binary_response = response.get_binary_response()
        print (f"in create_binary_register_response :Response: {response}")
        return binary_response


    def handle_response(self, parsed_request, is_request_successful):
        if not is_request_successful:
            self.send_error_response()
            return
        try:
            if parsed_request.code == RequestCode.REGISTER.value[0]:
                response = self.create_binary_register_response()
            elif parsed_request.code == RequestCode.GET_CLIENT_LIST.value:
                pass
            elif parsed_request.code == RequestCode.GET_PUBLIC_KEY.value:
                pass
            elif parsed_request.code == RequestCode.SEND_MESSAGE.value:
                pass
            elif parsed_request.code == RequestCode.GET_WAITING_MESSAGES.value:
                pass
            else:
                pass
            self.send_response(response)

        except Exception as e:
            print(f"Error handling response: {e}")
            self.send_error_response()
            print("error response sent from handle response")

    def send_response(self, response):
        self.client_handler.add_to_send_buf(response)


    def send_error_response(self):
        binary_error_response = Error_Response().get_binary_response()
        self.send_response(binary_error_response)


