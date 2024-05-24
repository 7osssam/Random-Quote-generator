#include "PasswordHandler.hpp"
#include "SystemMenu.hpp"
#include <algorithm>
#include <string>

void PasswordLengthHandler::setSuccessor(std::shared_ptr<Handler> next)
{
	successor_ = next;
}

bool PasswordLengthHandler::handleRequest(const std::string& str)
{
	if (str.length() < 8)
	{
		displayError("Password must be at least 8 characters long.");
		return false;
	}
	else if (successor_ != nullptr)
	{
		return successor_->handleRequest(str);
	}

	return true;
}

void PasswordDigitHandler::setSuccessor(std::shared_ptr<Handler> next)
{
	successor_ = next;
}

bool PasswordDigitHandler::handleRequest(const std::string& str)
{
	if (std::none_of(str.begin(), str.end(), ::isdigit))
	{
		displayError("Password must contain at least one digit.");
		return false;
	}
	else if (successor_ != nullptr)
	{
		return successor_->handleRequest(str);
	}
	return true;
}

void PasswordSpecialCharHandler::setSuccessor(std::shared_ptr<Handler> next)
{
	successor_ = next;
}

bool PasswordSpecialCharHandler::handleRequest(const std::string& str)
{
	if (std::none_of(str.begin(), str.end(), ::ispunct))
	{
		displayError("Password must contain at least one special character.");
		return false;
	}
	else if (successor_ != nullptr)
	{
		return true;
	}

	return true;
}