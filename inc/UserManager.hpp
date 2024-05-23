#ifndef __SECURE_H__
#define __SECURE_H__

#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <memory>
#include <map>
#include <algorithm>

#include "CSVManager.hpp"
#include "filesManager.hpp"

#define USERS_FILE "../data/users.csv"

// =================================================================================================

class Handler
{
public:
	virtual void setSuccessor(std::shared_ptr<Handler> next) = 0;
	virtual bool handleRequest(const std::string& str) = 0;
};

class PasswordLengthHandler : public Handler
{
private:
	std::shared_ptr<Handler> successor_;

public:
	void setSuccessor(std::shared_ptr<Handler> next) override
	{
		successor_ = next;
	}

	bool handleRequest(const std::string& str) override
	{
		if (str.length() < 8)
		{
			std::cout << "Password must be at least 8 characters long." << std::endl;
			return false;
		}
		else if (successor_ != nullptr)
		{
			return successor_->handleRequest(str);
		}

		return true;
	}
};

class PasswordDigitHandler : public Handler
{
private:
	std::shared_ptr<Handler> successor_;

public:
	void setSuccessor(std::shared_ptr<Handler> next) override
	{
		successor_ = next;
	}

	bool handleRequest(const std::string& str) override
	{
		if (std::none_of(str.begin(), str.end(), ::isdigit))
		{
			// TODO: display error message
			std::cout << "Password must contain at least one digit." << std::endl;
			return false;
		}
		else if (successor_ != nullptr)
		{
			return successor_->handleRequest(str);
		}
		return true;
	}
};

class PasswordSpecialCharHandler : public Handler
{
private:
	std::shared_ptr<Handler> successor_;

public:
	void setSuccessor(std::shared_ptr<Handler> next) override
	{
		successor_ = next;
	}

	bool handleRequest(const std::string& str) override
	{
		if (std::none_of(str.begin(), str.end(), ::ispunct))
		{
			std::cout << "Password must contain at least one special character." << std::endl;
			return false;
		}
		else if (successor_ != nullptr)
		{
			return true;
		}

		return true;
	}
};

// =================================================================================================

class Request
{
public:
	virtual bool handleRequest() = 0;
};

class RequestFactory
{
public:
	enum class RequestType
	{
		CREATE_PASSWORD,
		VERIFY_PASSWORD
	};

	static std::shared_ptr<Request> createRequest(RequestType						  type,
												  std::map<std::string, std::string>& users);
};

// this class is also the Client in the Chain of Responsibility pattern
class PasswordCreationRequest : public Request
{
private:
	std::map<std::string, std::string>&	  users;
	std::vector<std::shared_ptr<Handler>> handlers_;

public:
	PasswordCreationRequest(std::map<std::string, std::string>& users) : users(users)
	{
		// create the chain of responsibility
		handlers_.push_back(std::make_shared<PasswordLengthHandler>());
		handlers_.push_back(std::make_shared<PasswordDigitHandler>());
		handlers_.push_back(std::make_shared<PasswordSpecialCharHandler>());

		// set the successor for each handler
		handlers_[0]->setSuccessor(handlers_[1]);
		handlers_[1]->setSuccessor(handlers_[2]);
		handlers_[2]->setSuccessor(nullptr);
	}

	bool handleRequest() override;
};

class PasswordVerificationRequest : public Request
{
private:
	std::map<std::string, std::string>& users;

public:
	PasswordVerificationRequest(std::map<std::string, std::string>& users) : users(users)
	{
	}

	bool handleRequest() override;
};

class UserManager
{
private:
	FilesManager					   filesManager;
	CSVManager&						   csvManager_;
	std::map<std::string, std::string> users;
	std::shared_ptr<Request>		   createRequest;
	std::shared_ptr<Request>		   verifyRequest;

	void loadUsers();

	void saveUsers();

public:
	UserManager();

	bool createUser();

	bool verifyUser();

	bool isUsersEmpty();
};
#endif // __SECURE_H__