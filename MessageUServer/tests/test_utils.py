import unittest
import os
from unittest.mock import patch
from utils.utils_funcs import *

class TestUtils(unittest.TestCase):
    # Removes the file if it exists before each test
    def setUp(self):
        if os.path.exists(FILE_NAME):
            os.remove(FILE_NAME)

    # Cleans up after each test
    def tearDown(self):
        if os.path.exists(FILE_NAME):
            os.remove(FILE_NAME)

    # Creates a test file with a port number
    def test_read_port_from_file_success(self):
        test_port = 5000
        with open(FILE_NAME, 'w') as f:
            f.write(str(test_port))

        # Test that the function correctly reads the port
        result = read_port_from_file()
        self.assertEqual(result, test_port)

    # Test that the function returns the default port when file not found
    def test_read_port_from_file_not_found(self):
        result = read_port_from_file()
        self.assertEqual(result, DEFAULT_PORT)

    # Create a test file with invalid content
    def test_read_port_from_file_invalid_content(self):
        with open(FILE_NAME, 'w') as f:
            f.write("not_a_number")

        # Test that the function handles invalid content
        with self.assertRaises(ValueError):
            read_port_from_file()

    @patch('builtins.print')
    def test_read_port_from_file_prints_message(self, mock_print):
        # Test that the function prints the correct message when file not found
        read_port_from_file()
        mock_print.assert_any_call("File not found")
        mock_print.assert_any_call(f"Default port used: {DEFAULT_PORT}")


if __name__ == '__main__':
    unittest.main()