import utils
from services.selector_server import SelectorServer
import utils.defines as defaults
import utils.utils_funcs as utils

if __name__ == "__main__":
    try:
        port = utils.read_port_from_file()  #return the default port if file not found
        host = defaults.LOCALHOST
        print("Starting server on port: " ,port)
        mUserver = SelectorServer(host ,port)
        mUserver.connect()
    except Exception as e:
        print("Connection error in main : " , e) # TODO
