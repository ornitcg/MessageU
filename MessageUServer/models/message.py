import struct

class Message:
    def __init__(self, to_client, from_client, message_type, content, msg_id=None):
        self.msg_id = msg_id
        self.to_client = to_client
        self.message_type = message_type
        self.content = content
        self.message_size = len(content)
        self.from_client = from_client


    def __str__(self):
        return f"Message(to_client={self.to_client}, from_client={self.from_client}, message_type={self.message_type}, content={self.content})"

    def get_binary_message(self):
        binary_message = b""
        binary_message += self.from_client
        binary_message += struct.pack('<I', self.msg_id)
        binary_message += struct.pack('<B', self.message_type)
        binary_message += struct.pack('<I', self.message_size)
        binary_message += self.content
        return binary_message

    #getters
    def get_to_client(self):
        return self.to_client
    def get_from_client(self):
        return self.from_client
    def get_message_type(self):
        return self.message_type
    def get_content(self):
        return self.content
