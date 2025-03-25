#include "ListRequest.h"
#include "RequestInfo.h"

ListRequest::ListRequest(std::string& clientId) : BaseRequest(static_cast<uint16_t>(RequestCode::GET_CLIENT_LIST), clientId)
{
}

ListRequest::~ListRequest()
{
}
