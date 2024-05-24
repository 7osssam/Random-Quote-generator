#ifndef __CSVMANAGER_H__
#define __CSVMANAGER_H__

#include "FileManager.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

/**
	* @brief Parses a line of CSV data and returns a vector of strings representing each cell.
	* 
	* @param line The line of CSV data to be parsed.
	* @return std::vector<std::string> A vector of strings representing each cell in the line.
	*/
class CSVParseStrategy : public ParseStrategy
{
public:
	std::vector<std::string> parse(const std::string& line) override;
};

/**
 * @class CSVManager
 * @brief A class that manages CSV files and provides methods for loading, saving, and manipulating data.
 * @details CSVManager is a derived class of FileManager and implements the necessary methods for handling CSV files.
 */
class CSVManager : public FileManager
{
private:
	CSVManager(const CSVManager&) = delete;
	CSVManager& operator=(const CSVManager&) = delete;

	std::map<std::string, std::map<std::string, std::vector<std::string>>>
								   data_;		   /**< The data stored in the CSV file. */
	std::unique_ptr<ParseStrategy> parseStrategy_; /**< The strategy used for parsing the CSV file. */
	std::mutex					   mutex_;		   /**< Mutex for thread safety. */
	std::string					   filename_;	   /**< The filename of the CSV file. */

												   /**
	 * @brief Private constructor to enforce singleton pattern.
	 */
	CSVManager();

public:
	/**
	 * @brief Gets the singleton instance of CSVManager.
	 * @return The singleton instance of CSVManager.
	 */
	static CSVManager& getInstance(void);

	/**
	 * @brief Loads a CSV file.
	 * @param filename The filename of the CSV file to load.
	 * @return True if the file was loaded successfully, false otherwise.
	 */
	bool loadFile(const std::string& filename) override;

	/**
	 * @brief Gets the data from a specific column in the CSV file.
	 * @param filename The filename of the CSV file.
	 * @param column The name of the column to retrieve data from.
	 * @return A vector containing the data from the specified column.
	 */
	std::vector<std::string> getData(const std::string& filename, const std::string& column) override;

	/**
	 * @brief Sets the data for a specific column in the CSV file.
	 * @param filename The filename of the CSV file.
	 * @param column The name of the column to set data for.
	 * @param data The data to set for the specified column.
	 */
	void setData(const std::string& filename, const std::string& column,
				 const std::vector<std::string>& data) override;

	/**
	 * @brief Resets the data in the CSV file.
	 * @param filename The filename of the CSV file to reset.
	 * @return True if the data was reset successfully, false otherwise.
	 */
	bool resetData(const std::string& filename) override;

	/**
	 * @brief Saves the data to a CSV file.
	 * @param filename The filename of the CSV file to save.
	 * @return True if the file was saved successfully, false otherwise.
	 */
	bool saveFile(const std::string& filename) const override;
};

#endif // __CSVMANAGER_H__
