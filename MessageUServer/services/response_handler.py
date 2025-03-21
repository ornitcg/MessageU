from  models.base_response import *
from utils.defines import *
from models.register_response import *
import sys




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


    def handle_response(self, request_object, is_request_successful):
        print(f"DEBUG in Handling response for request: ")
        print(request_object)
        if not is_request_successful:
            self.send_error_response()
            return
        try:
            if request_object.code == RequestCode.REGISTER.value[0]:
                response = self.create_binary_register_response()
            elif request_object.code == RequestCode.GET_CLIENT_LIST.value[0]:
                response = self.create_binary_users_list_response()
            elif request_object.code == RequestCode.GET_PUBLIC_KEY.value[0]:
                pass
            elif request_object.code == RequestCode.SEND_MESSAGE.value[0]:
                pass
            elif request_object.code == RequestCode.GET_WAITING_MESSAGES.value[0]:
                pass
            else:
                pass
            print(f"Response: {response}")
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


    def create_binary_users_list_response(self):
        users_list = self.client_handler.get_client_list()
        # list_payload = get_biary_data_from_list(users_list)
        binary_names_list = from_tup_to_items(users_list)
        padded_binary = pad_list_items(binary_names_list, USER_NAME_SIZE , ZERO_CHAR)
        list_payload = concat_binary_items(padded_binary)
        print(len(list_payload))
        print(type(list_payload))

        client_id = self.client_handler.get_client_id()
        payload_size = CLIENT_ID_SIZE + len(list_payload)

        response = Users_List_Response(client_id, list_payload, payload_size)
        binary_response = response.get_binary_response()
        return binary_response