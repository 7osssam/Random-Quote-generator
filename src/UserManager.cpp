#include "../inc/UserManager.hpp"

#define MAX_TRIES 3

/**
 * @brief Generates a SHA-224 hash of the given string.
 * 
 * @param str The input string to be hashed.
 * @return std::string The SHA-224 hash of the input string.
 */
std::string generateSSHA224(const std::string& str)
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

// this class is also the Client in the Chain of Responsibility pattern
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

	users[username] = generateSSHA224(password);
	std::cout << "User created successfully.\n";

	return true;
}

bool PasswordVerificationRequest::handleRequest()
{
	std::string username;
	bool		isVerified = false;

	std::cout << "Enter username: ";
	std::cin >> username;

	if (users.find(username) == users.end())
	{
		std::cout << "User not found.\n";
		isVerified = false;
		return isVerified;
	}

	std::string password;
	std::cout << "Enter password: ";
	std::cin >> password;

	if (users[username] == generateSSHA224(password))
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

void UserManager::loadUsers()
{
	filesManager.loadFile(FileManagerFactory::FileType::CSV, USERS_FILE);

	auto users = filesManager.getData(FileManagerFactory::FileType::CSV, USERS_FILE, "username");
	auto passwords = filesManager.getData(FileManagerFactory::FileType::CSV, USERS_FILE, "passwd");

	for (size_t i = 0; i < users.size(); i++)
	{
		// store the username and password in the map
		this->users[users[i]] = passwords[i];
	}
}

void UserManager::saveUsers()
{
	std::vector<std::string> usernames;
	std::vector<std::string> passwords;

	for (const auto& user: users)
	{
		usernames.push_back(user.first);
		passwords.push_back(user.second);
	}

	filesManager.setData(FileManagerFactory::FileType::CSV, USERS_FILE, "username", usernames);
	filesManager.setData(FileManagerFactory::FileType::CSV, USERS_FILE, "passwd", passwords);

	// save file
	filesManager.saveFile(FileManagerFactory::FileType::CSV, USERS_FILE);
}

UserManager::UserManager() : csvManager_(CSVManager::getInstance())
{
	loadUsers();
}

bool UserManager::createUser()
{
	bool result =
		RequestFactory::createRequest(RequestFactory::RequestType::CREATE_PASSWORD, users)->handleRequest();

	saveUsers();

	return result;
}

bool UserManager::verifyUser()
{
	bool result =
		RequestFactory::createRequest(RequestFactory::RequestType::VERIFY_PASSWORD, users)->handleRequest();

	return result;
}

bool UserManager::isUsersEmpty()
{
	return users.empty();
}