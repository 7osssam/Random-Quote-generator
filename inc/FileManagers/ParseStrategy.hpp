#ifndef __PARSESTRATEGY_H__
#define __PARSESTRATEGY_H__

#include <string>
#include <vector>

/**
 * @brief The base class for parsing strategies.
 * 
 * This class defines the interface for parsing strategies used in the Random Quote Generator (CSV, TXT, JSON, etc.).
 * Subclasses of this class can implement different parsing algorithms to extract data from a string.
 */
class ParseStrategy
{
public:
	/**
	 * @brief Virtual destructor for ParseStrategy.
	 */
	virtual ~ParseStrategy() = default;

	/**
	 * @brief Parses a line of text and returns a vector of strings.
	 * 
	 * This pure virtual function should be implemented by subclasses to define their specific parsing algorithm.
	 * 
	 * @param line The line of text to be parsed.
	 * @return std::vector<std::string> A vector of strings extracted from the line.
	 */
	virtual std::vector<std::string> parse(const std::string& line) = 0;
};

#endif // __PARSESTRATEGY_H__