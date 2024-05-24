#ifndef __USERMANAGER_H__
#define __USERMANAGER_H__

#include <string>
#include <map>

#include "FilesManager.hpp"
#include "PasswordHandler.hpp"

/**
 * @brief The base class for handling requests.
 * 
 * The Request class is an abstract base class that defines the interface for handling requests.
 * Derived classes must implement the handleRequest() method to provide specific request handling logic.
 */
class Request
{
public:
	/**
	 * @brief Handles the request.
	 * 
	 * This pure virtual function must be implemented by derived classes to handle the request.
	 * 
	 * @return true if the request was handled successfully, false otherwise.
	 */
	virtual bool handleRequest() = 0;
};

/**
 * @brief The RequestFactory class is responsible for creating different types of requests.
 */
class RequestFactory
{
public:
	/**
	 * @brief Enum class representing different types of user requests.
	 */
	enum class RequestType
	{
		CREATE_PASSWORD, /**< Request to create a password. */
		VERIFY_PASSWORD	 /**< Request to verify a password. */
	};

	/**
	 * @brief Factory method to create a request based on the given type and user map.
	 * 
	 * @param type The type of the request.
	 * @param users The map of users.
	 * @return A shared pointer to the created request.
	 */
	static std::shared_ptr<Request> createRequest(RequestType						  type,
												  std::map<std::string, std::string>& users);
};

/**
 * @class PasswordCreationRequest
 * @brief Represents a request for password creation.
 *
 * The PasswordCreationRequest class is a derived class of the Request base class.
 * It handles the request for password creation by prompting the user to enter a new
 * username and password, and then validating the password using a chain of responsibility pattern.
 * If the password is valid, it stores the username and the hashed password in the users_ map.
 * @note This class is the client in the Chain of Responsibility design pattern.
 */
class PasswordCreationRequest : public Request
{
private:
	std::map<std::string, std::string>&	  users_;	 ///< Reference to a map of users.
	std::vector<std::shared_ptr<Handler>> handlers_; ///< Vector of handlers for password validation.

public:
	/**
	 * @brief Constructs a PasswordCreationRequest object.
	 *
	 * This constructor initializes a PasswordCreationRequest object with the given map of users.
	 * It also creates a chain of responsibility for password validation, consisting of three handlers:
	 * PasswordLengthHandler, PasswordDigitHandler, and PasswordSpecialCharHandler.
	 * The handlers are set up in a sequence and each handler is assigned a successor.
	 *
	 * @param users A reference to a map of users.
	 */
	PasswordCreationRequest(std::map<std::string, std::string>& users);

	/**
	 * Handles the request for password creation.
	 * 
	 * This function prompts the user to enter a new username and password. It then
	 * validates the password using a chain of responsibility pattern. If the password
	 * is valid, it stores the username and the hashed password in the users_ map.
	 * 
	 * @return True if the password creation is successful, false otherwise.
	 */
	bool handleRequest() override;
};

/**
 * @brief Represents a request for password verification.
 *
 * The `PasswordVerificationRequest` class is a subclass of `Request` and is used to handle password verification requests.
 * It prompts the user to enter a username and password, and verifies if the provided password matches the stored password for the given username.
 */
class PasswordVerificationRequest : public Request
{
private:
	std::map<std::string, std::string>&
		users_; /**< Reference to a map containing user information [username, password]. */

public:
	/**
	 * @brief Constructs a new PasswordVerificationRequest object.
	 *
	 * This constructor initializes a PasswordVerificationRequest object with the provided users map.
	 *
	 * @param users A reference to a map containing user information.
	 */
	PasswordVerificationRequest(std::map<std::string, std::string>& users);

	/**
	 * Handles the password verification request.
	 *
	 * This function prompts the user to enter a username and password, and verifies
	 * if the provided password matches the stored password for the given username.
	 * If the password is verified successfully, it returns true; otherwise, it returns false.
	 *
	 * @return True if the password is verified successfully, false otherwise.
	 */
	bool handleRequest() override;
};

/**
 * @brief The UserManager class is responsible for managing user data.
 * 
 * The UserManager class is responsible for managing user data, including creating new users and verifying existing users.
 * It uses the FilesManager class to read and write user data to a file. The user data is stored in a map where the key is the username and the value is the password.
 */
class UserManager
{
private:
	FilesManager					   filesManager_;
	std::map<std::string, std::string> users_;
	std::shared_ptr<Request>		   createRequest;
	std::shared_ptr<Request>		   verifyRequest;

	/**
	 * @brief Loads the users from a file and stores them in the `users_` map.
	 * 
	 * This function reads the usernames and passwords from a file using the `filesManager_` object.
	 * It then stores the usernames and passwords in the `users_` map, where the username is the key and the password is the value.
	 * 
	 * @note This function assumes that the file has already been loaded using the `filesManager_` object.
	 */
	void loadUsers();

	/**
	 * Saves the user data to a file.
	 * 
	 * This function retrieves the usernames and passwords from the users_ map
	 * and saves them to a file using the FilesManager class. The usernames are
	 * stored in a vector of strings and the passwords are stored in another
	 * vector of strings. The data is then set in the FilesManager object using
	 * the setData() function. Finally, the file is saved using the saveFile()
	 * function.
	 */
	void saveUsers();

public:
	/**
	 * @brief Constructs a new instance of the UserManager class.
	 * 
	 * This constructor initializes the UserManager object by calling the FileManagerFactory to create a FileManager object of type CSV.
	 * It then calls the loadUsers() function to load the users from the CSV file.
	 */
	UserManager();

	/**
	 * Creates a new user.
	 * 
	 * This function creates a new user by calling the createRequest function of the RequestFactory class
	 * with the request type set to CREATE_PASSWORD. The created request is then handled by the handleRequest
	 * function. After creating the user, the function saves the updated user list by calling the saveUsers function.
	 * 
	 * @return true if the user creation is successful, false otherwise.
	 */
	bool createUser();

	/**
	 * Verifies the user by creating a password verification request and handling it.
	 * 
	 * @return true if the user is verified successfully, false otherwise.
	 */
	bool verifyUser();

	/**
	 * @brief Checks if the user list is empty.
	 * 
	 * @return true if the user list is empty, false otherwise.
	 */
	bool isUsersEmpty();
};

#endif // __USERMANAGER_H__