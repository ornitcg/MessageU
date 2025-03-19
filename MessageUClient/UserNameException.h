#pragma once
#include <stdexcept>
#include <string>
#include "C:\Users\ornit\OneDrive\Documents\Defensive Programming\cryptopp-CRYPTOPP_8_8_0\cryptlib.h"
class UserNameException :  public std::runtime_error
{
public:
	UserNameException(const std::string& message) : std::runtime_error(message) {}
};

