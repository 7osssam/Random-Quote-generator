#include "UserManager.hpp"

#define MAX_TRIES  3
#define USERS_FILE "../data/users.csv"

#include <openssl/sha.h>
#include <iomanip> // std::setw, std::setfill

/**
 * @brief Generates a SHA-224 hash of the given string using the OpenSSL library. 
 * 
 * @param str The input string to be hashed.
 * @return std::string The SHA-224 hash of the input string.
 */
static std::string generateSSHA224(const std::string& str)
{
	unsigned char hash[SHA_DIGEST_LENGTH];

	SHA224(reinterpret_cast<const unsigned char*>(str.c_str()), str.length(), hash);

	std::stringstream ss;
	for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
	{
		ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
	}

	return ss.str();
}

std::shared_ptr<Request> RequestFactory::createRequest(RequestType						   type,
													   std::map<std::string, std::string>& users)
{
	switch (type)
	{
		case RequestType::CREATE_PASSWORD:
			return std::make_shared<PasswordCreationRequest>(users);
		case RequestType::VERIFY_PASSWORD:
			return std::make_shared<PasswordVerificationRequest>(users);
		default:
			return nullptr;
	}
}

PasswordCreationRequest::PasswordCreationRequest(std::map<std::string, std::string>& users) : users_(users)
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

bool PasswordCreationRequest::handleRequest()
{
	bool valid = false;
	int	 count = 0;

	std::string username;
	std::string password;

	std::cout << "Enter new username: ";
	std::cin >> username;

	while (!valid && count < MAX_TRIES)
	{
		std::cout << "Enter new password: ";
		std::cin >> password;

		// start the chain of responsibility
		if (handlers_[0]->handleRequest(password))
		{
			valid = true; // if the chain ends successfully, the password is valid
		}
		else
		{
			count++;
		}
	}

	if (count == MAX_TRIES)
	{
		std::cout << "Password creation failed.\n";
		return false;
	}

	users_[username] = generateSSHA224(password);
	std::cout << "User created successfully.\n";

	return true;
}

PasswordVerificationRequest::PasswordVerificationRequest(std::map<std::string, std::string>& users) :
	users_(users)
{
}

bool PasswordVerificationRequest::handleRequest()
{
	std::string username;
	bool		isVerified = false;

	std::cout << "Enter username: ";
	std::cin >> username;

	if (users_.find(username) == users_.end())
	{
		std::cout << "User not found.\n";
		isVerified = false;
		return isVerified;
	}

	std::string password;
	std::cout << "Enter password: ";
	std::cin >> password;

	if (users_[username] == generateSSHA224(password))
	{
		std::cout << "Password verified successfully.\n";
		isVerified = true;
	}
	else
	{
		std::cout << "Incorrect password.\n";
		isVerified = false;
	}

	return isVerified;
}

void UserManager::loadUsers()
{
	filesManager_.loadFile(USERS_FILE);

	auto users_ = filesManager_.getData(USERS_FILE, "username");
	auto passwords = filesManager_.getData(USERS_FILE, "passwd");

	for (size_t i = 0; i < users_.size(); i++)
	{
		// store the username and password in the map
		this->users_[users_[i]] = passwords[i];
	}
}

void UserManager::saveUsers()
{
	std::vector<std::string> usernames;
	std::vector<std::string> passwords;

	for (const auto& user: users_)
	{
		usernames.push_back(user.first);
		passwords.push_back(user.second);
	}

	filesManager_.setData(USERS_FILE, "username", usernames);
	filesManager_.setData(USERS_FILE, "passwd", passwords);

	// save file
	filesManager_.saveFile(USERS_FILE);
}

UserManager::UserManager() : filesManager_(FileManagerFactory::FileType::CSV)
{
	loadUsers();
}

bool UserManager::createUser()
{
	bool result =
		RequestFactory::createRequest(RequestFactory::RequestType::CREATE_PASSWORD, users_)->handleRequest();

	saveUsers();

	return result;
}

bool UserManager::verifyUser()
{
	bool result =
		RequestFactory::createRequest(RequestFactory::RequestType::VERIFY_PASSWORD, users_)->handleRequest();

	return result;
}

bool UserManager::isUsersEmpty()
{
	return users_.empty();
}