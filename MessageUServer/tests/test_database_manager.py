import unittest
import os
from data.database_manager import Database_Manager
from utils import utils_funcs as names


class TestDatabaseManager(unittest.TestCase):

    def setUp(self):
        """Sets up before each test"""
        # Change the database name for testing purposes
        names.DB_NAME = "test_defensive.db"
        self.db_manager = Database_Manager()
        # Connect to the database
        self.db_manager.initialize_db()
        self.db_manager.create_tables()

    def tearDown(self):
        """Cleans up after each test"""
        self.db_manager.disconnect()
        # Delete the test database file when done
        if os.path.exists(names.DB_NAME):
            os.remove(names.DB_NAME)

    def test_connect_and_create_tables(self):
        # Disconnect first
        self.db_manager.disconnect()
        # Test connection
        result = self.db_manager.connect()
        self.assertFalse(result)  # Should return False on success

        # Test table creation
        result = self.db_manager.create_tables()
        self.assertTrue(result)

    def test_add_and_get_client(self):
        """Test adding a client and retrieving by ID and username"""
        # Test client data
        client_id = b"0123456789abcdef"
        username = "test_user"
        public_key = b"a" * 160  # 160-byte public key

        # Add client
        result = self.db_manager.add_client(client_id, username, public_key)
        self.assertTrue(result)

        # Get client by ID
        client = self.db_manager.get_client_by_id(client_id)
        self.assertIsNotNone(client)
        self.assertEqual(client[0], client_id)
        self.assertEqual(client[1], username)
        self.assertEqual(client[2], public_key)

        # Get client by username
        client = self.db_manager.get_client_by_username(username)
        self.assertIsNotNone(client)
        self.assertEqual(client[0], client_id)

        # Try to add client with the same ID (should fail)
        result = self.db_manager.add_client(client_id, "another_user", public_key)
        self.assertFalse(result)

    def test_get_all_clients(self):
        """Test retrieving all clients"""
        # Add multiple clients
        clients = [
            (b"0123456789abcdef", "user1", b"a" * 160),
            (b"1123456789abcdef", "user2", b"b" * 160),
            (b"2123456789abcdef", "user3", b"c" * 160)
        ]

        for client in clients:
            self.db_manager.add_client(*client)

        # Get all clients
        all_clients = self.db_manager.get_all_clients()
        self.assertEqual(len(all_clients), 3)

        # Get all clients except one
        all_clients = self.db_manager.get_all_clients(exclude_id=b"0123456789abcdef")
        self.assertEqual(len(all_clients), 2)

    def test_update_client_last_seen(self):
        """Test updating client's last seen timestamp"""
        client_id = b"0123456789abcdef"
        username = "test_user"
        public_key = b"a" * 160

        # Add client
        self.db_manager.add_client(client_id, username, public_key)

        # Get initial data
        client = self.db_manager.get_client_by_id(client_id)
        initial_last_seen = client[3]

        # Wait briefly and update last seen
        import time
        time.sleep(1)
        result = self.db_manager.update_client_last_seen(client_id)
        self.assertTrue(result)

        # Verify last seen was updated
        client = self.db_manager.get_client_by_id(client_id)
        self.assertGreater(client[3], initial_last_seen)

    def test_add_and_get_messages(self):
        """Test adding messages and retrieving pending messages"""
        # Add clients
        client1_id = b"0123456789abcdef"
        client2_id = b"1123456789abcdef"

        self.db_manager.add_client(client1_id, "user1", b"a" * 160)
        self.db_manager.add_client(client2_id, "user2", b"b" * 160)

        # Add a message
        msg_type = 1  # Request for symmetric key
        msg_content = b"message content"

        result = self.db_manager.add_message(client2_id, client1_id, msg_type, msg_content)
        self.assertTrue(result)

        # Get pending messages
        messages = self.db_manager.get_pending_messages(client2_id)
        self.assertEqual(len(messages), 1)
        self.assertEqual(messages[0][0], client2_id)  # ToClient
        self.assertEqual(messages[0][1], client1_id)  # FromClient
        self.assertEqual(messages[0][2], msg_type)  # Type
        self.assertEqual(messages[0][3], msg_content)  # Content


if __name__ == "__main__":
    unittest.main()
