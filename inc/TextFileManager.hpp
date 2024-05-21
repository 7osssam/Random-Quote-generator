#ifndef __TEXTFILEMANAGER_H__
#define __TEXTFILEMANAGER_H__

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
 * @class TextParseStrategy
 * @brief A class that implements the ParseStrategy interface for parsing text.
 *
 * The TextParseStrategy class is responsible for parsing a single line of text and returning it as a single string in a vector.
 * It inherits from the ParseStrategy base class.
 */
class TextParseStrategy : public ParseStrategy
{
public:
    /**
	 * @brief Parses a single line of text.
	 * @param line The line of text to be parsed.
	 * @return A vector containing the parsed line as a single string.
	 *
	 * This function takes a single line of text and returns it as a single string in a vector.
	 */
    std::vector<std::string> parse(const std::string &line) override
    {
        return {line}; // Simply returns the line as a single string in a vector
    }
};

/**
 * @class TextFileManager
 * @brief A class that manages text files and provides methods for loading, saving, and manipulating data.
 * @details This class inherits from the FileManager base class and implements its pure virtual functions.
 */
class TextFileManager : public FileManager
{
private:
    /**
	 * @brief Private constructor to enforce singleton pattern.
	 */
    TextFileManager() : parseStrategy_(std::make_unique<TextParseStrategy>())
    {
    }

    TextFileManager(const TextFileManager &) = delete;
    TextFileManager &operator=(const TextFileManager &) = delete;

    std::map<std::string, std::vector<std::string>> data_; /**< A map that stores the loaded data from text files. */
    std::unique_ptr<ParseStrategy>
        parseStrategy_;    /**< A unique pointer to the parse strategy used for parsing text files. */
    std::mutex mutex_;     /**< A mutex used for thread safety when accessing and modifying the data. */
    std::string filename_; /**< The filename of the currently loaded text file. */

public:
    /**
	 * @brief Gets the singleton instance of the TextFileManager class.
	 * @return The singleton instance of the TextFileManager class.
	 */
    static TextFileManager &getInstance(void);

    /**
	 * @brief Loads the contents of a text file into memory.
	 * @param filename The name of the text file to load.
	 * @return True if the file was successfully loaded, false otherwise.
	 */
    bool loadFile(const std::string &filename) override;

    /**
	 * @brief Retrieves the data associated with a specific key from the loaded text file.
	 * @param filename The name of the text file.
	 * @param key The key associated with the data.
	 * @return A vector of strings containing the data associated with the key.
	 */
    std::vector<std::string> getData(const std::string &filename, const std::string &key) override;

    /**
	 * @brief Sets the data associated with a specific key in the loaded text file.
	 * @param filename The name of the text file.
	 * @param key The key to associate with the data.
	 * @param data The vector of strings containing the data to set.
	 */
    void setData(const std::string &filename, const std::string &key, const std::vector<std::string> &data) override;

    /**
	 * @brief Resets the data associated with a specific text file.
	 * @param filename The name of the text file.
	 * @return True if the data was successfully reset, false otherwise.
	 */
    bool resetData(const std::string &filename) override;

    /**
	 * @brief Saves the contents of the loaded text file to disk.
	 * @param filename The name of the text file to save.
	 * @return True if the file was successfully saved, false otherwise.
	 */
    bool saveFile(const std::string &filename) const override;
};

#endif // __TEXTFILEMANAGER_H__
