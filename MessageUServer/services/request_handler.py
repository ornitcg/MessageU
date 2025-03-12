import utils
from models.responses import *
from utils.defines import *
from models.register_request import RegisterRequest


class Request_Handler:
    def __init__(self, client_handler,  db_conn, db_mngr):
        self.client_handler = client_handler
        self.db_conn = db_conn
        self.db_mngr = db_mngr



    def handle_request(self, parsed_request):
        print(f"Request code: {parsed_request}")
        if parsed_request.code == RequestCode.REGISTER.value:
            print("Register request handle") # TODO DEBUG
            # self.register_client(parsed_request)
            print(f"Request: {parsed_request}") # TODO DEBUG
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


    def register_client(self, request):
        try:
            is_user_name_registered = self.db_conn.is_exists_client_username(self.client_handler.user_name)
            if is_user_name_registered:
                response = Error_Response(SERVER_VERSION)
                self.client_handler.add_to_send_buf(response.get_binary_response())
            else:
                self.client_handler.client_id = utils.generate_client_id()
                self.client_handler.public_key = request.public_key
                self.db_conn.add_client(self.client_handler.client_id, self.client_handler.user_name, self.client_handler.public_key)
                response = Base_Response(SERVER_VERSION, Response_Code.REGISTER_SUCCEEDED.value)
                self.client_handler.add_to_send_buf(response.get_binary_response())
        except Exception as e:
            print(f"Error registering client: {e}")
            response = Error_Response(SERVER_VERSION)
            self.client_handler.add_to_send_buf(response.get_binary_response())
            raise e


    def is_extract_complete_request(self, inb):
        print(f"Extracting whole request") # TODO DEBUG
        if len(inb) < REQUEST_HEADER_SIZE:
            return None
        print(f"Request size: {len(inb)}") # TODO DEBUG
        client_id, version, code, payload_size = self.parse_header(inb)
        request_size = REQUEST_HEADER_SIZE + payload_size
        if len(inb) < request_size:
            return None
        return request_size


    def parse_header(self, inb):
        client_id = inb[:CLIENT_ID_SIZE].decode()
        offset = CLIENT_ID_SIZE
        version = inb[offset:offset + VERSION_SIZE]
        offset += VERSION_SIZE
        code_bytes = inb[offset: offset + CODE_SIZE]
        code = int.from_bytes(code_bytes, byteorder='little')
        offset += CODE_SIZE
        payload_size = int.from_bytes(inb[offset:offset + PAYLOAD_SIZE], byteorder='little')
        offset += PAYLOAD_SIZE
        return client_id, version, code, payload_size

    def parse_request(self, inb):
        client_id, version, code, payload_size = self.parse_header(inb)
        offset = REQUEST_HEADER_SIZE
        payload = inb[offset:offset + payload_size]
        print(f"Client ID: {client_id}, Version: {version}, Code: {code}, Payload Size: {payload_size}, Payload: {payload}") # TODO DEBUG
        return self.generate_request_by_code(code, client_id, version, payload_size, payload)

    def generate_request_by_code(self, code, client_id, version, payload_size, payload):
        print(f"Code: {code}, Register value: {RequestCode.REGISTER.value[0]}")
        if code == RequestCode.REGISTER.value[0]:
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