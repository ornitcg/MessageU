#pragma once
#include "RegisterResponse.h"
#include <vector>
#include "Client.h"

class ListResponse :  public BaseResponse
{
private:
	std::vector<std::pair<std::string, Client>> clientsList;
	void parsePayload(std::string payload);

public:
	ListResponse(const BaseResponse& header , std::string payload);
	~ListResponse();
	std::vector<std::pair<std::string, Client>>& getClientsList();
};

