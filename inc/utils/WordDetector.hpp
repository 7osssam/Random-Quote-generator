#ifndef __WORDDETECTOR_H__
#define __WORDDETECTOR_H__

#include "FilesManager.hpp"
#include <algorithm>

#define WORDS_FILE "../data/Words.csv"

/**
 * @class WordDetector
 * @brief Singleton class for detecting words in a text.
 *
 * The WordDetector class provides functionality to detect words in a given text.
 * It follows the Singleton design pattern to ensure that only one instance of the class exists.
 */
class WordDetector
{
private:
	FilesManager filesManager_;

	/**
	 * @brief Constructs a new instance of the WordDetector class.
	 * 
	 * This constructor initializes a WordDetector object by loading a CSV file using the FileManagerFactory.
	 * The file to be loaded is specified by the WORDS_FILE constant.
	 */
	WordDetector();

	WordDetector(const WordDetector&) = delete;
	WordDetector& operator=(const WordDetector&) = delete;

	/**
	 * @brief Splits a string into a vector of words based on a delimiter.
	 * 
	 * @param s The string to be split.
	 * @param delimiter The character used to split the string.
	 * @return std::vector<std::string> The vector of words obtained after splitting the string.
	 */
	std::vector<std::string> split(const std::string& s, char delimiter);

public:
	/**
	 * @brief Singleton class for detecting words in a text.
	 *
	 * The WordDetector class provides functionality to detect words in a given text.
	 * It follows the Singleton design pattern to ensure that only one instance of the class exists.
	 */
	static WordDetector& getInstance();

	/**
	 * Checks if a given line contains a word from a specified emotion.
	 *
	 * @param emotion The emotion to search for.
	 * @param line The line to search within.
	 * @return True if the line contains a word from the specified emotion, false otherwise.
	 */
	bool containsWord(const std::string& emotion, const std::string& line);
};

#endif // __WORDDETECTOR_H__