

class Client:
    def __init__(self, client_id, user_name, public_key, last_seen):
        self.client_id = client_id
        self.user_name = user_name
        self.public_key = public_key
        self.last_seen = None

    #getters setters
    def get_client_id(self):
        return self.client_id

    def set_client_id(self, id):
        if not self.client_id:
            self.client_id = id
        else:
            raise Exception("[ERROR] Client ID already set")


    def get_user_name(self):
        return self.user_name

    def get_public_key(self):
        return self.public_key

    def get_last_seen(self):
        return self.last_seen

    def set_last_seen(self, last_seen):
        self.last_seen = last_seen

