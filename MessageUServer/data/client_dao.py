import sqlite3
from datetime import datetime, timezone


class Client_Dao:
    def __init__(self, conn, cursor):
        self.conn = conn
        self.cursor = cursor

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
            print("[ERROR] Error creating clients table ", e)
            return False

    def is_exists_client_username(self, username):
        try:
            self.cursor.execute("SELECT * FROM clients WHERE UserName=?", (username,))
            if self.cursor.fetchone():
                return True
            return False
        except sqlite3.Error as e:
            print("[ERROR] Error searching client ", e)
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
            print("[ERROR] Error adding client ", e)
            return False

    def get_client_by_id(self, client_id):
        try:
            self.cursor.execute("SELECT * FROM clients WHERE ID=?", (client_id,))
            return self.cursor.fetchone()
        except sqlite3.Error as e:
            print("[ERROR] Error getting client ", e)
            return None

    def get_public_key_by_id(self, client_id):
        try:
            self.cursor.execute("SELECT PublicKey FROM clients WHERE ID=?", (client_id,))
            return self.cursor.fetchone()
        except sqlite3.Error as e:
            print("[ERROR] Error getting client ", e)
            return None

    def get_client_by_username(self, username):
        try:
            self.cursor.execute("SELECT * FROM clients WHERE UserName=?", (username,))
            return self.cursor.fetchone()
        except sqlite3.Error as e:
            print("[ERROR] Error getting client ", e)
            return None

    def get_all_clients(self, exclude_id=None):
        try:
            if exclude_id:
                self.cursor.execute("SELECT ID ,UserName FROM clients WHERE ID != ?", (exclude_id,))
            else:
                self.cursor.execute("SELECT ID, UserName FROM clients")
            return self.cursor.fetchall()
        except sqlite3.Error as e:
            print("[ERROR] Error getting clients ", e)
            return []

    def update_client_last_seen(self, client_id):
        try:
            current_time = datetime.now(timezone.utc).isoformat()
            self.cursor.execute("UPDATE clients SET LastSeen = ? WHERE ID=?", (current_time ,client_id,))
            self.conn.commit()
            return True
        except sqlite3.Error as e:
            print("[ERROR] Error updating last seen ", e)
            return False