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

def get_binary_data_from_list(list):
    return b''.join(name.encode() for name in list)


def from_tup_to_items(list):
    items = [tup[0] for tup in list]
    return items

def pad_list_items(list,max,char):
    return [item.ljust(max,char) for item in list]


def concat_binary_items(list):
    binary_str =  ''.join(item for item in list)
    return binary_str.encode()