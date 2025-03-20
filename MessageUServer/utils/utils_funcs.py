from utils.server_messages import *
from utils.names import *
from utils.defines import *


def read_port_from_file():
    try:
        with open(FILE_NAME, 'r') as f:
            return int(f.read())

    except FileNotFoundError:
        print(FILE_NOT_FOUND)
        print(DEFAULT_PORT_USED)
        return DEFAULT_PORT


def names_list_to_binary(users_list):
    binary_users_list = b''
    for user_name in users_list:
        binary_user_name = user_name.encode()
        binary_users_list += binary_user_name + b'\0'
    return binary_users_list