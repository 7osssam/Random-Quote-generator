#ifndef __QUOTEMANAGER_H__
#define __QUOTEMANAGER_H__

#include "FilesManager.hpp"

#include <algorithm>
#include <string>
#include <vector>

#define QUOTES_FILE "../data/Quotes.csv"

/**
 * @class QuoteManager
 * @brief Manages the retrieval of random quotes based on emotions.
 *
 * The QuoteManager class is responsible for managing the retrieval of random quotes
 * based on different emotions. It provides a singleton instance to ensure that only
 * one instance of the QuoteManager class exists throughout the application.
 */
class QuoteManager
{
private:
	FilesManager			 filesManager_;
	std::vector<std::string> history_;

	/**
	 * @brief Constructs a new instance of the QuoteManager class.
	 * 
	 * This constructor initializes the QuoteManager object by setting the FileManager type to CSV
	 * and loading the quotes file using the FileManager instance.
	 */
	QuoteManager();

	QuoteManager(const QuoteManager&) = delete;
	QuoteManager& operator=(const QuoteManager&) = delete;

public:
	/**
	 * @class QuoteManager
	 * @brief Singleton class for managing quotes.
	 *
	 * The `QuoteManager` class provides a singleton instance for managing quotes in the application.
	 * It ensures that only one instance of `QuoteManager` is created and provides a global point of access to it.
	 * The `getInstance` method returns a reference to the singleton instance.
	 */
	static QuoteManager& getInstance();

	/**
	 * @brief Retrieves a random quote based on the specified emotion.
	 * 
	 * @param emotion The emotion to filter the quotes by.
	 * @return A random quote as a string.
	 *         If no quotes are available for the specified emotion, returns "No quotes available for this emotion."
	 */
	std::string getRandomQuote(const std::string& emotion);

	/**
	 * @brief Returns the history of quotes.
	 * 
	 * This function returns a constant reference to the history of quotes stored in a vector of strings.
	 * 
	 * @return A constant reference to the history of quotes.
	 */
	std::vector<std::string> getHistory() const;

	/**
	 * @brief Sets the history of quotes.
	 *
	 * This function sets the history of quotes in the `QuoteManager` class.
	 * The history is represented as a vector of strings.
	 *
	 * @param history The vector of strings representing the history of quotes.
	 */
	void setHistory(const std::vector<std::string>& history);
};

#endif // __QUOTEMANAGER_H__