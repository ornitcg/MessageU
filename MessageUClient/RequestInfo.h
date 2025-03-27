
#pragma once
#include <string>
#include <vector>
#include "UImanager.h"




// request codes as they appear in the protocol
enum class RequestCode : uint16_t {
	REGISTER = 600,
	GET_CLIENT_LIST = 601,
	GET_PUBLIC_KEY = 602,
	SEND_MESSAGE = 603,
	GET_WAITING_MESSAGES = 604
};


// message types as they appear in the protocol
enum class MessageType : uint8_t {
	NONE = 0, // used as placeholder in vector. Not a real message type
	GET_SYM_KEY = 1,
	SEND_SYM_KEY = 2,
	SEND_TEXT_MESSAGE = 3,
	SEND_FILE = 4
};



// Structure for a  request type  record
struct RequestInfo {
	MenuOption menuOption;       
	RequestCode protocolCode;    
	MessageType messageType;    
	std::string description;     // description as requested in mmn
};

// storage of all requests information
const std::vector<std::pair<MenuOption, RequestInfo>> requestInfoVector = {
	{MenuOption::REGISTER, {MenuOption::REGISTER, RequestCode::REGISTER, MessageType::NONE, "Register with the server"}},
	{MenuOption::GET_CLIENT_LIST, {MenuOption::GET_CLIENT_LIST, RequestCode::GET_CLIENT_LIST, MessageType::NONE, "Request for clients list"}},
	{MenuOption::GET_PUBLIC_KEY, {MenuOption::GET_PUBLIC_KEY, RequestCode::GET_PUBLIC_KEY, MessageType::NONE, "Request for public key"}},
	{MenuOption::GET_WAITING_MESSAGES, {MenuOption::GET_WAITING_MESSAGES, RequestCode::GET_WAITING_MESSAGES, MessageType::NONE, "Request for waiting messages"}},
	{MenuOption::SEND_TEXT_MESSAGE, {MenuOption::SEND_TEXT_MESSAGE, RequestCode::SEND_MESSAGE, MessageType::SEND_TEXT_MESSAGE, "Send a text message"}},
	{MenuOption::GET_SYMMETRIC_KEY, {MenuOption::GET_SYMMETRIC_KEY, RequestCode::SEND_MESSAGE, MessageType::GET_SYM_KEY , "Send a request for symmetric key"}},
	{MenuOption::SEND_SYMMETRIC_KEY, {MenuOption::SEND_SYMMETRIC_KEY, RequestCode::SEND_MESSAGE, MessageType::SEND_SYM_KEY, "Send your symmetric key"}},
	{MenuOption::SEND_FILE, {MenuOption::SEND_FILE, RequestCode::SEND_MESSAGE, MessageType::SEND_FILE , "Send a file"}},
	{MenuOption::EXIT, {MenuOption::EXIT, RequestCode(0), MessageType::NONE, "Exit client"}}
};

// Helper functions to work with this structure

bool isValidChoice(int choice);
RequestCode getProtocolCode(MenuOption option);