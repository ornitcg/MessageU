class Message:
    def __init__(self, target_id, sender_id, message_type, content, msg_id=None):
        self.msg_id = None
        self.to_client = target_id
        self.from_client = sender_id
        self.message_type = message_type
        self.content = content

    def __str__(self):
        return f"Message(to_client={self.to_client}, from_client={self.from_client}, message_type={self.message_type}, content={self.content})"


    #getters
    def get_to_client(self):
        return self.to_client
    def get_from_client(self):
        return self.from_client
    def get_message_type(self):
        return self.message_type
    def get_content(self):
        return self.content
