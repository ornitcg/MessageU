import utils
from models.base_response import *
from utils.defines import *
from models.register_request import RegisterRequest



class Request_Handler:
    def __init__(self, client_handler,  db_mngr):
        self.client_handler = client_handler
        self._db_mngr = db_mngr

    def get_client_handler(self):
        return self.client_handler


    def getDBmngr(self):
        return self._db_mngr


    def handle_request(self, parsed_request):
        try:
            if parsed_request.code == RequestCode.REGISTER.value[0]:
                return self.register_client(parsed_request)

                # response = Register_Response(self.client_handler.get_binary_client_id())
                # print(f"in register_client : Response: {response}")  # TODO DEBUG
                # self.client_handler.add_to_send_buf(response.get_binary_response())
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
        except Exception as e:
            print(f"Error handling request: {e}")
            raise e


    def register_client(self, request):
        try:
            client_handler = self.get_client_handler()
            client_handler.update_client_with_request_payload(request)
            is_user_name_registered = self._db_mngr.is_exists_client_username(client_handler.user_name)
            if is_user_name_registered:
                raise Exception("User name already registered")
            else:
                client_handler.generate_client_id()
                binary_client_id = self.client_handler.get_binary_client_id()
                print(f"in register_client new UUID: {binary_client_id}")

                user_name = self.client_handler.get_user_name()
                public_key = self.client_handler.get_public_key()
                self._db_mngr.add_client(binary_client_id ,user_name, public_key)
                return True
        except Exception as e:
            print(f"Error registering client: {e}")
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
        version = int.from_bytes(inb[offset:offset + VERSION_SIZE], byteorder='little')
        offset += VERSION_SIZE
        code_bytes = inb[offset: offset + CODE_SIZE]
        print(f"in parse_header Code bytes: {code_bytes}") # TODO DEBUG
        code = int.from_bytes(code_bytes, byteorder='little')
        offset += CODE_SIZE
        payload_size = int.from_bytes(inb[offset:offset + PAYLOAD_SIZE], byteorder='little')
        offset += PAYLOAD_SIZE
        return client_id, version, code, payload_size

    def parse_request(self, inb):
        client_id, version, code, payload_size = self.parse_header(inb)
        offset = REQUEST_HEADER_SIZE
        payload = (inb[offset:offset + payload_size])
        print(f"in parse_request Client ID: {client_id}, Version: {version}, Code: {code}, Payload Size: {payload_size}, Payload: {payload}") # TODO DEBUG
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