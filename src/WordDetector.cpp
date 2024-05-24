#include "../inc/WordDetector.hpp"

WordDetector::WordDetector() : filesManager_{FileManagerFactory::FileType::CSV}
{
	filesManager_.loadFile(WORDS_FILE);
}

std::vector<std::string> WordDetector::split(const std::string& s, char delimiter)
{
	std::vector<std::string> words;
	std::stringstream		 ss(s);
	std::string				 word;

	while (std::getline(ss, word, delimiter))
	{
		// Skip empty words
		if (!word.empty())
		{
			words.push_back(word);
		}
	}

	return words;
}

WordDetector& WordDetector::getInstance()
{
	static WordDetector instance;
	return instance;
}

bool WordDetector::containsWord(const std::string& emotion, const std::string& line)
{
	bool result = false;
	auto words = filesManager_.getData(WORDS_FILE, emotion);

	//split the line into words
	std::vector<std::string> lineWords = split(line, ' ');

	// search in a line a word from the words vector
	for (const auto& word: words)
	{
		if (std::find(lineWords.begin(), lineWords.end(), word) != lineWords.end())
		{
			result = true;
			break;
		}
	}
	return result;
}