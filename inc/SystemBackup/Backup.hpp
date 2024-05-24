#ifndef __BACKUP_H__
#define __BACKUP_H__

#include "FilesManager.hpp"
#include "QuoteManager.hpp"
#include <vector>

// Memento class
class Memento
{
private:
	std::vector<std::string> history_; /**< The history stored in the Memento object. */

public:
	/**
	 * @brief Constructs a new Memento object with the given history.
	 * 
	 * @param history The history to be stored in the Memento.
	 */
	Memento(const std::vector<std::string>& history);

	/**
	 * @brief Returns the history stored in the Memento object.
	 * 
	 * This function returns a constant reference to the history vector
	 * stored in the Memento object. The history vector contains a list
	 * of strings representing the historical state of the object.
	 * 
	 * @return A constant reference to the history vector.
	 */
	std::vector<std::string> getHistory() const;
};

// Caretaker class
class Caretaker
{
private:
	std::unique_ptr<Memento> memento_;		/**< The Memento object used to store the state of the object. */
	FilesManager			 filesManager_; /**< The FilesManager object used to manage file operations. */
	QuoteManager&			 quoteManager_; /**< The QuoteManager object used to manage quotes. */

public:
	/**
	 * @brief Constructs a new Caretaker object.
	 *
	 * This constructor initializes a Caretaker object by creating instances of FileManager and QuoteManager.
	 * The FileManager instance is created with the FileType set to Text.
	 * The QuoteManager instance is obtained using the getInstance() method.
	 */
	Caretaker();

	/**
	 * @brief Creates a backup of the quote history.
	 * 
	 * This function creates a backup of the quote history by saving it to a file.
	 * It first creates a memento object to store the current state of the quote history.
	 * Then, it loads the backup file and sets its data to an empty string.
	 * After that, it sets the data of the backup file to the current state of the quote history.
	 * Finally, it saves the backup file using the filesManager.
	 * 
	 * @return true if the backup is successful, false otherwise.
	 */
	bool backup();

	/**
	 * Restores the state of the object to a previous state.
	 *
	 * @return true if the restoration is successful, false otherwise.
	 */
	bool restore();
};

#endif // __BACKUP_H__