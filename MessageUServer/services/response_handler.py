from  models.base_response import *
from models.register_response import *
from models.public_key_response import *
from models.message_response import *
from models.waiting_messages_response import *
from utils.defines import *



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
        return binary_response


    def handle_response(self, request_object, is_request_successful):
        msgs_request = False  #flag for message request (used for deleting message from DB)
        msg_id_list = [] #list of message ids to delete
        if not is_request_successful:
            self.send_error_response()
            return
        try:
            if request_object.code == RequestCode.REGISTER.value[0]:
                response = self.create_binary_register_response()
            elif request_object.code == RequestCode.GET_CLIENT_LIST.value[0]:
                response = self.create_binary_users_list_response()
            elif request_object.code == RequestCode.GET_PUBLIC_KEY.value[0]:
                response = self.create_binary_public_key_response()
            elif request_object.code == RequestCode.MESSAGE.value[0]:
                response = self.create_binary_message_response()
            elif request_object.code == RequestCode.GET_WAITING_MESSAGES.value[0]:
                response , msg_id_list = self.create_binary_waiting_messages_response()
                msgs_request = True
            else:
                pass

            self.send_response(response)
            if msgs_request == True:
                self.db_mngr.delete_messages(msg_id_list)
        except Exception as e:
            print(f"[ERROR] Error handling response: {e}")
            self.send_error_response()
            print("[LOG] Error response sent from handle response")

    def send_response(self, response):
        self.client_handler.add_to_send_buf(response)


    def send_error_response(self):
        binary_error_response = Error_Response().get_binary_response()
        self.send_response(binary_error_response)


    def create_binary_users_list_response(self):
        users_list = self.client_handler.get_client_list()
        list_payload = get_binary_list_payload(users_list, USER_NAME_SIZE, ZERO_CHAR)
        payload_size = len(list_payload)
        response = Users_List_Response(list_payload, payload_size)
        binary_response = response.get_binary_response()
        return binary_response

    def create_binary_waiting_messages_response(self):
        waiting_messages = self.db_mngr.get_pending_messages(self.client_handler.get_client_id())
        if waiting_messages is None:
            print("[LOG] No waiting messages")
            raise Exception("[ERROR] No waiting messages")
        msg_id_list = [message.get_msg_id() for message in waiting_messages]
        response = Waiting_Messages_Response(waiting_messages)
        return response.get_binary_response(), msg_id_list



    def create_binary_public_key_response(self):
        target_public_key = self.client_handler.get_target_public_key()
        target_client_id = self.client_handler.get_target_client_id()
        if target_public_key is None:
            print("[LOG] Public key not found")
            raise Exception("[ERROR] Public key not found")
        response = Public_Key_Response(target_client_id, target_public_key)
        binary_response = response.get_binary_response()
        return binary_response


    def create_binary_message_response(self):
        #do according to message object message type
        messageRequest = self.client_handler.get_parsed_request()
        messageType = messageRequest.get_message_type()
        if messageType not in Message_Type:
            raise Exception("[ERROR] Invalid message type")
        msg_id = self.client_handler.get_message_id()
        target_client_id = self.client_handler.get_request_object().get_target_client_id()
        response = Message_Response(msg_id, target_client_id)
        binary_response = response.get_binary_response()
        return binary_response
