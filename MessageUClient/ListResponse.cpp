#include "ListResponse.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include "Client.h"
#include "CurrentClient.h"

ListResponse::ListResponse(const BaseResponse& header, std::string payload)
	: BaseResponse(header.getVersion(), header.getCode(), header.getPayloadSize())
{	
	try {
		parsePayload(payload);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}		
}

ListResponse::~ListResponse()
{
}

void ListResponse::parsePayload(std::string payload)
{
	int singleRecordSize = MAX_NAME_SIZE + CLIENT_ID_SIZE +1;
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
		offset += MAX_NAME_SIZE + 1;	
		memcpy(&id[0], payload.data() + offset, CLIENT_ID_SIZE);
		offset += CLIENT_ID_SIZE;
		Client newClient = Client(id, name);
		
		name = removeZeroPadding(name);
		clientsList.push_back(std::make_pair(name, newClient));
	}
	
}





std::vector<std::pair<std::string, Client>>& ListResponse::getClientsList() 
{
	return clientsList;
}


