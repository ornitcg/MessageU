import utils
from selector_server import SelectorServer

if __name__ == "__main__":
    port = utils.read_port_from_file()
    print(port)

    mUserver = SelectorServer(port)
    try:
        mUserver.connect()
        mUserver.accept()
    except Exception as e:
        print("Connection error: " , e)
