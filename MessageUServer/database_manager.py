import sqlite3
import constants.names as names


class DatabaseManager:
    def __init__(self):
        self.conn = None
        self.cursor = None

    # manages the connection to the database
    def connect(self):
        try:
            self.conn = sqlite3.connect(names.DB_NAME)
            self.cursor = self.conn.cursor()
        except sqlite3.Error as e:
            print("Error connecting to DB ", e)
            return True

    def initialize_db(self):
        try:
            self.connect()
            self.create_tables()
        except sqlite3.Error as e:
            print("Error initializing the database ", e)
            return False

    def create_clients_table(self):
        try:
            self.cursor.execute('''CREATE TABLE IF NOT EXISTS clients
                                (ID BLOB(16) PRIMARY KEY, 
                                UserName TEXT NOT NULL,
                                PublicKey BLOB(160) NOT NULL, 
                                LastSeen INTEGER NOT NULL)''')
            self.conn.commit()
            return True
        except sqlite3.Error as e:
            print("Error creating clients table ", e)
            return False

    def create_messages_table(self):
        try:
            self.cursor.execute('''CREATE TABLE IF NOT EXISTS messages
                                (ToClient BLOB(16) NOT NULL, 
                                FromClient BLOB(16) NOT NULL,
                                Type INTEGER NOT NULL, 
                                Content BLOB,
                                FOREIGN KEY(ToClient) REFERENCES clients(ID),
                                FOREIGN KEY(FromClient) REFERENCES clients(ID))''')
            self.conn.commit()
            return True
        except sqlite3.Error as e:
            print("Error creating messages table ", e)
            return False

    def create_tables(self):
        if self.create_clients_table() and self.create_messages_table():
            return True
        return False


    def disconnect(self):
        if self.conn:
            self.conn.close()
            self.conn = None
            self.cursor = None

    def is_exists_client_username(self, username):
        try:
            self.cursor.execute("SELECT * FROM clients WHERE UserName=?", (username,))
            if self.cursor.fetchone():
                return True
            return False
        except sqlite3.Error as e:
            print("Error searching client ", e)
            raise e





    def add_client(self, client_id, username, public_key):
        try:
            self.cursor.execute(
                "INSERT INTO clients (ID, UserName, PublicKey, LastSeen) VALUES (?, ?, ?, CURRENT_TIMESTAMP)",
                (client_id, username, public_key)
            )

            self.conn.commit()
            return True

        except sqlite3.IntegrityError as e:
            print("Error adding client ", e)
            return False



    def get_client_by_id(self, client_id):
        try:
            self.cursor.execute("SELECT * FROM clients WHERE ID=?", (client_id,))
            return self.cursor.fetchone()
        except sqlite3.Error as e:
            print("Error getting client ", e)

    def get_client_by_username(self, username):
        try:
            self.cursor.execute("SELECT * FROM clients WHERE UserName=?", (username,))
            return self.cursor.fetchone()
        except sqlite3.Error as e:
            print("Error getting client ", e)
            return False

    def get_all_clients(self, exclude_id=None):
        try:
            if exclude_id:
                self.cursor.execute("SELECT * FROM clients WHERE ID != ?", (exclude_id,))
            else:
                self.cursor.execute("SELECT * FROM clients")
            return self.cursor.fetchall()
        except sqlite3.Error as e:
            print("Error getting clients ", e)
            return False

    def update_client_last_seen(self, client_id):
        try:
            self.cursor.execute("UPDATE clients SET LastSeen = CURRENT_TIMESTAMP WHERE ID=?", (client_id,))
            self.conn.commit()
            return True
        except sqlite3.Error as e:
            print("Error updating last seen ", e)
            return False

    def add_message(self, to_client, from_client, message_type, content):
        try:
            self.cursor.execute(
                "INSERT INTO messages (ToClient, FromClient, Type, Content) VALUES (?, ?, ?, ?)",
                (to_client, from_client, message_type, content)
            )
            self.conn.commit()
            return True
        except sqlite3.Error as e:
            print("Error adding message ", e)
            return False

    def get_pending_messages(self, client_id):
        try:
            self.cursor.execute("SELECT * FROM messages WHERE ToClient=?", (client_id,))
            return self.cursor.fetchall()
        except sqlite3.Error as e:
            print("Error getting messages ", e)
            return False

    def delete_message(self, message_id):
        try:
            self.cursor.execute("DELETE FROM messages WHERE ID=?", (message_id,))
            self.conn.commit()
            return True
        except sqlite3.Error as e:
            print("Error deleting message ", e)
            return False
