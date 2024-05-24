#ifndef __PASSWORDHANDLER_H__
#define __PASSWORDHANDLER_H__

#include <memory>

/**
 * @brief The Handler class is an abstract base class that defines the interface for handling password requests.
 */
class Handler
{
public:
	/**
	 * @brief Destructor for the Handler class.
	 */
	virtual ~Handler() = default;

	/**
	 * @brief Sets the next handler in the chain of responsibility.
	 * 
	 * @param next A shared pointer to the next handler.
	 */
	virtual void setSuccessor(std::shared_ptr<Handler> next) = 0;

	/**
	 * @brief Handles the password request.
	 * 
	 * @param str The password string to be handled.
	 * @return True if the request is handled successfully, false otherwise.
	 */
	virtual bool handleRequest(const std::string& str) = 0;
};

class PasswordLengthHandler : public Handler
{
private:
	std::shared_ptr<Handler> successor_;

public:
	/**
	 * Sets the successor handler for the PasswordLengthHandler.
	 * 
	 * @param next The next handler to be set as the successor.
	 */
	void setSuccessor(std::shared_ptr<Handler> next) override;

	/**
	 * Handles the request to check the length of a password.
	 * 
	 * @param str The password string to be checked.
	 * @return True if the password length is at least 8 characters long, false otherwise.
	 */
	bool handleRequest(const std::string& str) override;
};

class PasswordDigitHandler : public Handler
{
private:
	std::shared_ptr<Handler> successor_;

public:
	/**
	 * Sets the successor handler for the PasswordDigitHandler.
	 *
	 * @param next The shared pointer to the next handler in the chain.
	 */
	void setSuccessor(std::shared_ptr<Handler> next) override;

	/**
	 * Handles the request to check if the password contains at least one digit.
	 *
	 * @param str The password string to be checked.
	 * @return True if the password contains at least one digit, false otherwise.
	 */
	bool handleRequest(const std::string& str) override;
};

class PasswordSpecialCharHandler : public Handler
{
private:
	std::shared_ptr<Handler> successor_;

public:
	/**
	 * Sets the successor handler for the PasswordSpecialCharHandler.
	 * 
	 * @param next The next handler to be set as the successor.
	 */
	void setSuccessor(std::shared_ptr<Handler> next) override;

	/**
	 * Handles the request for the PasswordSpecialCharHandler class.
	 *
	 * This function processes the given string and performs the necessary operations
	 * to handle the request. It takes a constant reference to a string as a parameter.
	 *
	 * @param str The string to be processed.
	 * @return True if the string contains at least one special character, false otherwise.
	 */
	bool handleRequest(const std::string& str) override;
};

#endif // __PASSWORDHANDLER_H__