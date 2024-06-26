#ifndef __FILESMANAGER_H__
#define __FILESMANAGER_H__

#include "FileManagerFactory.hpp"
#include <string>
#include <vector>
#include <memory>

/**
 * @brief The FilesManager class handles file operations for different file types.
 * @note This class is a Facade that simplifies the use of FileManager objects as a single interface
 */
class FilesManager
{
private:
	FileManager* manager_;

public:
	FilesManager(FileManagerFactory::FileType type);

	/**
	 * @brief Loads a file of the specified type and filename.
	 * 
	 * @param type The type of the file to load.
	 * @param filename The name of the file to load.
	 * @return True if the file is loaded successfully, false otherwise.
	 */
	bool loadFile(const std::string& filename) const;

	/**
	 * @brief Retrieves data from a file of the specified type, filename, and key.
	 * 
	 * @param type The type of the file to retrieve data from.
	 * @param filename The name of the file to retrieve data from.
	 * @param key The key associated with the data to retrieve.
	 * @return A vector of strings containing the retrieved data.
	 */
	std::vector<std::string> getData(const std::string& filename, const std::string& key) const;

	/**
	 * @brief Sets data in a file of the specified type, filename, and key.
	 * 
	 * @param type The type of the file to set data in.
	 * @param filename The name of the file to set data in.
	 * @param key The key associated with the data to set.
	 * @param data The vector of strings containing the data to set.
	 */
	void setData(const std::string& filename, const std::string& key,
				 const std::vector<std::string>& data) const;

	/**
	 * @brief Resets data in a file of the specified type and filename.
	 * 
	 * @param type The type of the file to reset data in.
	 * @param filename The name of the file to reset data in.
	 * @return True if the data is reset successfully, false otherwise.
	 */
	bool resetData(const std::string& filename) const;

	/**
	 * @brief Saves a file of the specified type and filename.
	 * 
	 * @param type The type of the file to save.
	 * @param filename The name of the file to save.
	 * @return True if the file is saved successfully, false otherwise.
	 */
	bool saveFile(const std::string& filename) const;

	/**
	 * @brief Destructor for the FilesManager class.
	 */
	~FilesManager();
};

#endif // __FILESMANAGER_H__
