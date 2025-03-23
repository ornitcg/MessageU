#include "ListResponse.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include "Client.h"
#include "CurrentClient.h"

ListResponse::ListResponse(uint8_t version, uint16_t code, uint32_t payloadSize, std::string payload)
	: RegisterResponse(version, code, payloadSize, payload)
{	
	//print payloaseSize and payload size
	
	if (payloadSize > 0)
		parsePayload(payload);
		
}

ListResponse::~ListResponse()
{
}

void ListResponse::parsePayload(std::string payload)
{
	int singleRecordSize = MAX_NAME_SIZE + CLIENT_ID_SIZE + 1;
	if ((this->getPayloadSize() % singleRecordSize) != 0) {
		throw std::runtime_error("Error: List size is invalid");
	}
	int usersCount = this->getPayloadSize() / singleRecordSize;
	uint32_t offset = 0;
	for (int i = 0; i < usersCount; i++) {
		
		std::string name;		
		name.resize(MAX_NAME_SIZE);
		std::string id;
		id.resize(CLIENT_ID_SIZE);
		
		memcpy(&name[0], payload.data() + offset, MAX_NAME_SIZE);
		offset += MAX_NAME_SIZE;	
		memcpy(&id[0], payload.data() + offset, CLIENT_ID_SIZE);
		offset += CLIENT_ID_SIZE;
		Client newClient = Client(id, name);
		clientList.push_back(std::make_pair(name, newClient));
	}
	
}

void ListResponse::displayClientList()
{
	if (clientList.size() == 0) {
		std::cout << "No clients registered" << std::endl;
	}
	else {
		for (auto& client : clientList) {
			std::cout << client.first << std::endl;
		}
	}
	
}

void ListResponse::sortClientList()
{
	std::sort(clientList.begin(), clientList.end(), [](const std::pair<std::string, Client>& a, const std::pair<std::string, Client>& b) {
		return a.second < b.second;
		});
	
}

std::vector<std::pair<std::string, Client>>& ListResponse::getClientList() 
{
	return clientList;
}


