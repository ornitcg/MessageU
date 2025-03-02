import sqlite3
import constants.names as names

class DatabaseManager:
    def __init__(self):
        self.db_name = names.DB_NAME
        self.conn = None
        self.cursor = None

    #manages the connection to the database
    def connect(self):
        try:
            self.conn = sqlite3.connect(self.db_name)
            self.cursor = self.conn.cursor()
        except sqlite3.Error as e:
            print("Error connecting to DB ", e)
            return True

    #creates the clients table
    def create_clients_table(self):
        try:
            self.cursor.execute('''CREATE TABLE IF NOT EXISTS clients
                                (ID BLOB(16) PRIMARY KEY, 
                                UserName TEXT NOT NULL,
                                PublicKey BLOB(160) NOT NULL, 
                                LastSeen INTEGER NOT NULL)''')
            self.conn.commit()
        except sqlite3.Error as e:
            print("Error creating clients table ", e)
            return False

    #creates the messages table
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
        except sqlite3.Error as e:
            print("Error creating messages table ", e)
            return False

    #calls to create_clients_table and create_messages_table
    def create_tables(self):
        if self.create_clients_table() and self.create_messages_table():
            return True
        return False

    #initialize the database
    def init_db(self):
        if self.connect():
            return self.create_tables()

    def disconnect(self):
        if self.conn:
            self.conn.close()
            self.conn = None
            self.cursor = None


    #adds a new client to database. if client id exists , it will notify the user
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

