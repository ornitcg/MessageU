#include "ListRequest.h"
#include "RequestInfo.h"

ListRequest::ListRequest(std::string& clientId) : BaseRequest(clientId, static_cast<uint16_t>(RequestCode::GET_CLIENT_LIST), static_cast<uint32_t>(NO_PAYLOAD))
{
}

ListRequest::~ListRequest()
{
}
