import sqlite3


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
            print("Error creating messages table ", e)
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
            return []

    def delete_message(self, message_id):
        try:
            self.cursor.execute("DELETE FROM messages WHERE ID=?", (message_id,))
            self.conn.commit()
            return True
        except sqlite3.Error as e:
            print("Error deleting message ", e)
            return False