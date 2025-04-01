
from models.register_request import *
from models.public_key_request import *
from models.message_request import *
from models.clients_list_request import *
from models.waiting_messages_request import *
import pprint



class Request_Handler:
    def __init__(self, client_handler,  db_mngr):
        self.client_handler = client_handler
        self.db_mngr = db_mngr
        self.header = None

    def get_client_handler(self):
        return self.client_handler


    def get_DB_mngr(self):
        return self.db_mngr

    def set_client_list(self, client_list):
        self.client_handler.set_client_list(client_list)

    def handle_request(self, request_object):
        code = request_object.get_code()
        try:
            if code == RequestCode.REGISTER.value[0]:
                return self.register_client(request_object)
            elif code == RequestCode.GET_CLIENT_LIST.value[0]:
                self.client_handler.set_client_with_request_object(request_object)
                return self.get_client_list(request_object)
            elif code == RequestCode.GET_PUBLIC_KEY.value[0]:
                return self.get_target_public_key(request_object)
            elif code == RequestCode.MESSAGE.value[0]:
                return self.handle_send_message(request_object)  #saves message in DB
            elif code == RequestCode.GET_WAITING_MESSAGES.value[0]:
                return True
            else:
                pass
        except Exception as e:
            print(f"[ERROR] Error handling request: {e}")
            raise e


    def register_client(self, request):
        try:
            client_handler = self.get_client_handler()
            client_handler.update_client_with_request_payload(request)
            is_user_name_registered = self.db_mngr.is_exists_client_username(client_handler.user_name)
            if is_user_name_registered:
                raise Exception("[ERROR] User name already registered")
            else:
                client_handler.generate_client_id()
                binary_client_id = self.client_handler.get_binary_client_id()
                user_name = self.client_handler.get_user_name()
                public_key = self.client_handler.get_public_key()
                self.db_mngr.add_client(binary_client_id, user_name, public_key)
                return True
        except Exception as e:
            print(f"[ERROR] Error registering client: {e}")
            raise e


    def is_extract_complete_request(self, inb):
        if len(inb) < REQUEST_HEADER_SIZE:
            return None
        self.parse_header(inb)
        request_size = REQUEST_HEADER_SIZE + self.header.get_payload_size()
        if len(inb) < request_size:
            return None
        return request_size

    def parse_header(self, inb):
        client_id = inb[:CLIENT_ID_SIZE]
        if not self.client_handler.get_client_id():
            self.client_handler.set_client_id(client_id)

        offset = CLIENT_ID_SIZE
        version = int.from_bytes(inb[offset:offset + VERSION_SIZE], byteorder='little')
        offset += VERSION_SIZE
        code_bytes = inb[offset: offset + CODE_SIZE]
        code = int.from_bytes(code_bytes, byteorder='little')
        offset += CODE_SIZE
        payload_size = int.from_bytes(inb[offset:offset + PAYLOAD_SIZE], byteorder='little')
        offset += PAYLOAD_SIZE
        self.header = Base_Request(client_id, version, code, payload_size)

    def get_request_object(self, inb):
        offset = REQUEST_HEADER_SIZE
        payload = (inb[offset:])
        return self.generate_request_by_code(payload)

    def generate_request_by_code(self, payload):
        code = self.header.get_code()
        if code == RequestCode.REGISTER.value[0]:
            return Register_Request(self.header, payload)
        elif code == RequestCode.GET_CLIENT_LIST.value[0]:
            return Clients_List_Request(self.header)
        elif code == RequestCode.GET_PUBLIC_KEY.value[0]:
            return Public_Key_Request(self.header, payload)
        elif code == RequestCode.MESSAGE.value[0]:
            return Message_Request(self.header, payload)
        elif code == RequestCode.GET_WAITING_MESSAGES.value[0]:
            return self.header
        else:
            return None

    def get_client_list(self, request_object):
        client_id = request_object.get_client_id()
        try:
            client_list = self.db_mngr.get_all_clients(exclude_id = client_id)
            self.set_client_list(client_list)
            return True
        except Exception as e:
            print(f"[ERROR] Error getting client list: {e}")
            raise e


    def get_target_public_key(self, request_object):
        target_client_id = request_object.get_target_client_id()
        try:
            target_public_key = self.db_mngr.get_public_key_by_id(target_client_id)
            if target_public_key:
                self.client_handler.set_target_public_key(target_public_key[0])
                self.client_handler.set_target_client_id(target_client_id)
                return True
            else:
                raise Exception("[ERROR] Client not found")
        except Exception as e:
            print(f"[ERROR] Error getting public key: {e}")
            raise e


    def handle_send_message(self, message_request_object):
        try:
            message = message_request_object.get_message()
            msg_id = self.db_mngr.add_message(message)
            self.client_handler.set_message_id(msg_id)
            return True
        except Exception as e:
            print(f"[ERROR] Error sending message: {e}")
            raise e


