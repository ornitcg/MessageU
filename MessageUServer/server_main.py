import utils
from selector_server import SelectorServer
import constants.defines as defaults

if __name__ == "__main__":
    try:
        port = utils.read_port_from_file()  #return the default port if file not found
        host = defaults.LOCALHOST
        print("Starting server on port: " ,port)
        mUserver = SelectorServer(host ,port)
        mUserver.connect()
    except Exception as e:
        print("Connection error in main : " , e) # TODO DEBUG
