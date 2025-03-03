from constants.server_messages import *
from constants.names import *


def read_port_from_file():
    try:
        with open(FILE_NAME, 'r') as f:
            return int(f.read())

    except FileNotFoundError:
        print(FILE_NOT_FOUND)
        print(DEFAULT_PORT_USED)
        return DEFAULT_PORT
