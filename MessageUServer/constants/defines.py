import enum

DEFAULT_PORT = 1357
MAX_CONNECTIONS = 50
MAX_BUFFER_SIZE = 4096
REQUEST_HEADER_SIZE = 23
LOCALHOST = "127.0.0.1"
CLIENT_ID_SIZE = 16
VERSION_SIZE = 1
SERVER_VERSION = 2
CODE_SIZE = 2
PAYLOAD_SIZE = 4
USER_NAME_SIZE = 255
PUBLIC_KEY_SIZE = 160
MESSAGE_TYPE = 1
CONTENT_SIZE = 4

class ResponseCode(enum):
    REGISTER_SUCEEDED = 2100,
    CLIENT_LIST = 2101,
    PUBLIC_KEY = 2102,
    MESSAGE_SENT = 2103,
    WAITING_MESSAGES = 2104,
    GENERAL_ERROR = 9000

class RequestCode(enum):
    REGISTER = (600, "Register a new client")
    GET_CLIENT_LIST = (601, "Get the list of clients")
    GET_PUBLIC_KEY = (602, "Get the public key of a client")
    SEND_MESSAGE = (603, "Send a message to a client")
    GET_WAITING_MESSAGES = (604, "Get waiting messages for a client")


