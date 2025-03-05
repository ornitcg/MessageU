#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "utils.h"
#include <vector>
#include <array>

//returns array with IP and port, read from file
std::array<std::string,2> getServerIPfromFile(std::string fileName) {
	std::string serverIP = "";
	std::string port = "";
	std::string line;
	std::ifstream file(fileName, std::ios::binary);
	if (!file) {
		std::cerr << "Failed to open file " << fileName << std::endl;
	}
	else if (std::getline(file, line)){
		std::stringstream ss(line);
		std::getline(ss, serverIP, ':');
		std::getline(ss, port);
		
	}
	return{ serverIP, port };
}

