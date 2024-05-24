#ifndef __WORDDETECTOR_H__
#define __WORDDETECTOR_H__

#include "FilesManager.hpp"
#include <algorithm>

#define WORDS_FILE "../data/Words.csv"

class WordDetector
{
private:
	FilesManager filesManager_;
	WordDetector();

	WordDetector(const WordDetector&) = delete;
	WordDetector& operator=(const WordDetector&) = delete;

	std::vector<std::string> split(const std::string& s, char delimiter);

public:
	// create singleton
	static WordDetector& getInstance();

	bool containsWord(const std::string& emotion, const std::string& line);
};

#endif // __WORDDETECTOR_H__