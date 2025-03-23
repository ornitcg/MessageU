#include "PublicKeyRequest.h"
#include "RequestInfo.h"


PublicKeyRequest::PublicKeyRequest(std::string& clientId) : BaseRequest(static_cast<uint16_t>(RequestCode::GET_PUBLIC_KEY), CLIENT_ID_SIZE)
{
	this->clientId = clientId;
}

PublicKeyRequest::~PublicKeyRequest()
{
}

std::string PublicKeyRequest::getBinaryRequest()
{
	std::string binaryData = getBinaryHeader();
	binaryData.append(clientId);
	return binaryData;
}
