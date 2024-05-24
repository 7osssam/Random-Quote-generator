#ifndef __FILEMANAGER_H__
#define __FILEMANAGER_H__

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <vector>

#include "ParseStrategy.hpp"
#include <string>

/**
 * @class FileManager
 * @brief Abstract class for managing file operations.
 * 
 * The FileManager class provides an interface for loading, saving, and manipulating data in files.
 * It is an abstract class that must be inherited and implemented by concrete file managers.
 */
class FileManager
{
public:
	/**
	 * @brief Destructor for FileManager.
	 */
	virtual ~FileManager() = default;

	/**
	 * @brief Loads data from a file.
	 * 
	 * @param filename The name of the file to load.
	 * @return True if the file was successfully loaded, false otherwise.
	 */
	virtual bool loadFile(const std::string& filename) = 0;

	/**
	 * @brief Retrieves data from a file based on a key.
	 * 
	 * @param filename The name of the file to retrieve data from.
	 * @param key The key associated with the data.
	 * @return A vector of strings containing the data associated with the key.
	 */
	virtual std::vector<std::string> getData(const std::string& filename, const std::string& key) = 0;

	/**
	 * @brief Sets data in a file based on a key.
	 * 
	 * @param filename The name of the file to set data in.
	 * @param key The key associated with the data.
	 * @param data The vector of strings containing the data to set.
	 */
	virtual void setData(const std::string& filename, const std::string& key,
						 const std::vector<std::string>& data) = 0;

	/**
	 * @brief Resets data in a file.
	 * 
	 * @param filename The name of the file to reset data in.
	 * @return True if the data was successfully reset, false otherwise.
	 */
	virtual bool resetData(const std::string& filename) = 0;

	/**
	 * @brief Saves data to a file.
	 * 
	 * @param filename The name of the file to save.
	 * @return True if the file was successfully saved, false otherwise.
	 */
	virtual bool saveFile(const std::string& filename) const = 0;
};

#endif // __FILEMANAGER_H__