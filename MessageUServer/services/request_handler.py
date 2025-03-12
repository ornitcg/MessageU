import utils
from models.base_response import BaseResponse
from utils.defines import *
from models.register_request import RegisterRequest


class RequestHandler:
    def __init__(self, client_handler,  db_conn, db_mngr):
        self.client_handler = client_handler
        self.db_conn = db_conn
        self.db_mngr = db_mngr


    def handle_request(self, request):
        if request.code == RequestCode.REGISTER.value:
            print("Register request handle") # TODO DEBUG
            # register_client(client, request, db_conn)
            print(f"Request: {request}") # TODO DEBUG
        elif request.code == RequestCode.GET_CLIENT_LIST.value:
            pass
        elif request.code == RequestCode.GET_PUBLIC_KEY.value:
            pass
        elif request.code == RequestCode.SEND_MESSAGE.value:
            pass
        elif request.code == RequestCode.GET_WAITING_MESSAGES.value:
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


    def is_extract_complete_request(self, inb):
        print(f"Extracting whole request") # TODO DEBUG
        if len(inb) < REQUEST_HEADER_SIZE:
            return None
        print(f"Request size: {len(inb)}") # TODO DEBUG
        return self.parse_request(inb)

    def parse_request(self, inb):
        client_id = inb[:CLIENT_ID_SIZE].decode()
        offset = CLIENT_ID_SIZE
        version = inb[offset:offset + VERSION_SIZE]
        offset += VERSION_SIZE
        code = inb[offset: offset + CODE_SIZE].decode()
        offset += CODE_SIZE
        # payload_size = self.inb[offset:offset + PAYLOAD_SIZE].decode()
        payload_size = int.from_bytes(inb[offset:offset + PAYLOAD_SIZE], byteorder='little')
        offset += PAYLOAD_SIZE
        payload = inb[offset:offset + payload_size]
        print(f"Client ID: {client_id}, Version: {version}, Code: {code}, Payload Size: {payload_size}, Payload: {payload}") # TODO DEBUG
        return self.generate_request_by_code(code, client_id, version, payload_size, payload)

    def generate_request_by_code(self, code, client_id, version, payload_size, payload):
        if code == RequestCode.REGISTER.value:
            print(" generate_request_by_code RegisterRequest") # TODO DEBUG
            return RegisterRequest(client_id, version, code, payload_size, payload)
        # elif code == RequestCode.GET_CLIENT_LIST[0]:
        #     return GetClientListRequest(client_id, version, code, payload_size, payload)
        # elif code == RequestCode.GET_PUBLIC_KEY[0]:
        #     return GetPublicKeyRequest(client_id, version, code, payload_size, payload)
        # elif code == RequestCode.SEND_MESSAGE[0]:
        #     return SendMessageRequest(client_id, version, code, payload_size, payload)
        # elif code == RequestCode.GET_WAITING_MESSAGES[0]:
        #     return GetWaitingMessagesRequest(client_id, version, code, payload_size, payload)
        else:
            return None