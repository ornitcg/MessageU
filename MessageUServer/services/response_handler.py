class ResponseHandler:
    def __init__(self, client_handler, db_conn, db_mngr):
        self.client_handler = client_handler
        self.db_conn = db_conn
        self.db_mngr = db_mngr