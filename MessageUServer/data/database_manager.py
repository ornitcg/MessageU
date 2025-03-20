import sqlite3
from utils import utils_funcs as names
from data.client_dao import *
from data.message_dao import *


class Database_Manager:
    def __init__(self):
        self.conn = None
        self.cursor = None
        self.client_dao = None
        self.message_dao = None

    # manages the connection to the database
    def connect(self):
        try:
            self.conn = sqlite3.connect(names.DB_NAME)
            self.cursor = self.conn.cursor()
            self.client_dao = Client_Dao(self.conn, self.cursor)
            self.message_dao = Message_Dao(self.conn, self.cursor)
            return True
        except sqlite3.Error as e:
            print("ERROR: Error connecting to DB ", e)
            return False

    def initialize_db(self):
        try:
            self.connect()
            self.create_tables()
            return True
        except sqlite3.Error as e:
            print("ERROR: Error initializing the database ", e)
            return False

    def table_exists(self, table_name):
        try:
            self.cursor.execute("SELECT name FROM sqlite_master WHERE type='table' AND name=?", (table_name,))
            if self.cursor.fetchone():
                return True
            return False
        except sqlite3.Error as e:
            print("Error checking table ", e)
            return False

    def create_tables(self):
        clients_created = self.client_dao.create_clients_table()
        messages_created = self.message_dao.create_messages_table()
        return clients_created and messages_created


    def disconnect(self):
        if self.conn:
            self.conn.close()
            self.conn = None
            self.cursor = None
            self.client_dao = None # Reset the DAOs
            self.message_dao = None # Reset the DAOs

    def is_exists_client_username(self, username):
        return self.client_dao.is_exists_client_username(username)

    def add_client(self, client_id, username, public_key):
        return self.client_dao.add_client(client_id, username, public_key)

    def get_client_by_id(self, client_id):
        return self.client_dao.get_client_by_id(client_id)

    def get_client_by_username(self, username):
        return self.client_dao.get_client_by_username(username)

    def get_all_clients(self, exclude_id=None):
        return self.client_dao.get_all_clients(exclude_id)

    def update_client_last_seen(self, client_id):
        return self.client_dao.update_client_last_seen(client_id)

    def add_message(self, to_client, from_client, message_type, content):
        return self.message_dao.add_message(to_client, from_client, message_type, content)

    def get_pending_messages(self, client_id):
        return self.message_dao.get_pending_messages(client_id)

    def delete_message(self, message_id):
        return self.message_dao.delete_message(message_id)

