#include "PublicKeyRequest.h"
#include "RequestInfo.h"


PublicKeyRequest::PublicKeyRequest(std::string& payloadClientId) : BaseRequest(static_cast<uint16_t>(RequestCode::GET_PUBLIC_KEY), CLIENT_ID_SIZE)
{
	this->payloadClientId = payloadClientId;
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
