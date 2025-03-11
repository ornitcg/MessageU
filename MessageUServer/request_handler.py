import utils
from base_response import BaseResponse
from constants.defines import *




class RequestHandler:
    def __init__(self,  db_conn):
        self.db_conn = db_conn


    def perform_request(self, client, request, db_conn ):
        if request.code == RequestCode.REGISTER[0]:
            print("Register request performing") # TODO DEBUG
            return "Register response"
            # register_client(client, request, db_conn)
        elif request.code == RequestCode.GET_CLIENT_LIST[0]:
            pass
        elif request.code == RequestCode.GET_PUBLIC_KEY[0]:
            pass
        elif request.code == RequestCode.SEND_MESSAGE[0]:
            pass
        elif request.code == RequestCode.GET_WAITING_MESSAGES[0]:
            pass
        else:
            pass


    def register_client(client, request, db_conn):
        try:
            is_registered = db_conn.is_exists_client_username(client.user_name)
            if is_registered:
                response = BaseResponse(SERVER_VERSION, ResponseCode.GENERAL_ERROR)
                client.add_to_send_buf(response.get_binary_response())
            else:
                client.client_id = utils.generate_client_id()
                client.public_key = request.public_key
                db_conn.add_client(client.client_id, client.user_name, client.public_key)
                response = BaseResponse(SERVER_VERSION, ResponseCode.REGISTER_SUCCEEDED)
                client.add_to_send_buf(response.get_binary_response())
        except Exception as e:
            print(f"Error registering client: {e}")
            response = BaseResponse(SERVER_VERSION, ResponseCode.GENERAL_ERROR)
            client.add_to_send_buf(response.get_binary_response())
            raise e