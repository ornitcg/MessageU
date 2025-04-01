import sqlite3
from models.message import Message

class Message_Dao:
    def __init__(self, conn, cursor):
        self.conn = conn
        self.cursor = cursor

    def create_messages_table(self):
        try:
            self.cursor.execute('''CREATE TABLE IF NOT EXISTS messages
                                (ID INTEGER PRIMARY KEY AUTOINCREMENT,
                                ToClient BLOB(16) NOT NULL, 
                                FromClient BLOB(16) NOT NULL,
                                Type INTEGER NOT NULL, 
                                Content BLOB,
                                FOREIGN KEY(ToClient) REFERENCES clients(ID),
                                FOREIGN KEY(FromClient) REFERENCES clients(ID))''')
            self.conn.commit()
            return True
        except sqlite3.Error as e:
            print("[ERROR] Error creating messages table ", e)
            return False

    def add_message(self, message):
        try:
            self.cursor.execute(
                "INSERT INTO messages (ToClient, FromClient, Type, Content) VALUES (?, ?, ?, ?)",
                (message.get_to_client(), message.get_from_client(), message.get_message_type(), message.get_content())
            )
            self.conn.commit()
            return self.cursor.lastrowid
        except sqlite3.Error as e:
            print("[ERROR] Error adding message ", e)
            return None

    def get_pending_messages(self, client_id):
        try:
            self.cursor.execute("SELECT * FROM messages WHERE ToClient=?", (client_id,))
            msg_records =  self.cursor.fetchall()
            msg_objects = []
            for rec in msg_records:
                message = Message(rec[1], rec[2], rec[3], rec[4], rec[0])
                msg_objects.append(message)
            return msg_objects

        except sqlite3.Error as e:
            print("[ERROR] Error getting messages ", e)
            return []

    def delete_message(self, message_id):
        try:
            self.cursor.execute("DELETE FROM messages WHERE ID=?", (message_id,))
            self.conn.commit()
            return True
        except sqlite3.Error as e:
            print("[ERROR] Error deleting message ", e)
            return False