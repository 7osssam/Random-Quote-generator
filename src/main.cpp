#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <vector>
#include <string>
#include <memory>
#include <array>
#include <mutex>
#include <map>
#include <algorithm>
#include <cstdlib> // For rand() and srand() functions

// Strategy pattern for parsing CSV data
class ParseStrategy
{
public:
	virtual ~ParseStrategy() = default;
	virtual std::vector<std::string> parse(const std::string& line) = 0;
};

class CSVParseStrategy : public ParseStrategy
{
public:
	std::vector<std::string> parse(const std::string& line) override
	{
		std::vector<std::string> result;
		std::string				 cell;
		std::istringstream		 lineStream(line);

		while (std::getline(lineStream, cell, ','))
		{
			result.push_back(cell);
		}
		return result;
	}
};

// Singleton pattern for CSV Manager
class CSVManager
{
private:
	CSVManager() = default;

	std::map<std::string, std::map<std::string, std::vector<std::string>>> data_;
	std::unique_ptr<ParseStrategy>										   parseStrategy_;
	std::mutex															   mutex_;

public:
	static CSVManager& getInstance()
	{
		static CSVManager instance;
		return instance;
	}

	// Disable copy constructor and assignment operator
	CSVManager(const CSVManager&) = delete;
	CSVManager& operator=(const CSVManager&) = delete;

	bool loadFile(const std::string& filename)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		std::ifstream				file(filename);

		// array of static variables to set flag for each file loaded
		static std::vector<bool> fileLoaded(10, false);

		// get filename index in the vector of data_ map to check with fileLoaded vector
		auto it = data_.find(filename);
		int	 index = std::distance(data_.begin(), it);

		// check if file is already loaded
		if (fileLoaded[index] == true)
		{
			std::cerr << "File already loaded: " << filename << std::endl;
			return false;
		}

		// set flag for in the fileLoaded vector for the corresponding index
		fileLoaded[index] = true;

		if (!file.is_open())
		{
			std::cerr << "Failed to open file: " << filename << std::endl;
			return false;
		}

		std::string line;
		if (std::getline(file, line))					// Read header
		{
			auto headers = parseStrategy_->parse(line); // Get headers

			// Initialize data map for this file
			data_[filename] = {};
			for (const auto& header: headers)
			{
				data_[filename][header] = {};
			}

			// Read data rows
			while (std::getline(file, line))
			{
				auto values = parseStrategy_->parse(line); // Parse values
				for (size_t i = 0; i < headers.size(); ++i)
				{
					if (i < values.size())
					{
						data_[filename][headers[i]].push_back(values[i]); // Store values
					}
					else
					{
						data_[filename][headers[i]].push_back("");		  // Add empty value if missing
					}
				}
			}
		}
		else
		{
			std::cerr << "Empty file: " << filename << std::endl;
			return false;
		}

		return true;
	}

	std::vector<std::string> getData(const std::string& filename, const std::string& column)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		if (data_.find(filename) != data_.end())
		{
			if (data_[filename].find(column) != data_[filename].end())
			{
				return data_[filename][column];
			}
		}
		return {};
	}

	void setParseStrategy(std::unique_ptr<ParseStrategy> strategy)
	{
		parseStrategy_ = std::move(strategy);
	}
};

// Factory pattern for creating parse strategies
class ParseStrategyFactory
{
public:
	enum StrategyType
	{
		CSV_format_t
	};

	static std::unique_ptr<ParseStrategy> createStrategy(StrategyType type)
	{
		switch (type)
		{
			case CSV_format_t:
				return std::make_unique<CSVParseStrategy>();
			default:
				throw std::invalid_argument("Unknown strategy type");
		}
	}
};

// New: QuoteManager class
class QuoteManager
{
private:
	CSVManager& csvManager_;

public:
	QuoteManager(CSVManager& csvManager) : csvManager_(csvManager)
	{
	}

	std::string getRandomQuote(const std::string& filename, const std::string& emotion)
	{
		auto quotes = csvManager_.getData(filename, emotion);
		if (!quotes.empty())
		{
			int index = rand() % quotes.size();
			return quotes[index];
		}
		return "No quotes available for this emotion.";
	}
};

// this should have an instance of CSVManager and check for a specific words in the CSV based on the filename and emotion (column name)
class WordDetector
{
private:
	CSVManager& csvManager_;

	std::vector<std::string> split(const std::string& s, char delimiter)
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

public:
	WordDetector(CSVManager& csvManager) : csvManager_(csvManager)
	{
	}

	bool containsWord(const std::string& filename, const std::string& emotion, const std::string& line)
	{
		bool result = false;
		auto words = csvManager_.getData(filename, emotion);

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
};

#define WORDS_FILE	"../data/Words.csv"
#define QUOTES_FILE "../data/Quotes.csv"
#define BUILD_DIR	"../build"

// TODO: the output should be outputed in a log file
// look https://github.com/odundar/simple_cpp_logger/blob/master/Logger.hpp
bool systemInit()
{
	// Get the current path
	std::filesystem::path currentPath = std::filesystem::current_path();
	std::cout << "Current path is " << currentPath << '\n';

	// Define the expected build directory path
	std::filesystem::path buildDirectory = "../build";
	std::filesystem::path fullBuildPath = std::filesystem::absolute(buildDirectory);

	std::cout << "Expected build directory path is " << fullBuildPath << '\n';

	// Check if the program is running from the build directory
	if (currentPath != fullBuildPath)
	{
		std::cerr << "Please run the program from the build directory" << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Running the program from the build directory" << std::endl;

	return EXIT_SUCCESS;
}

int main()
{
	srand(time(nullptr)); // Initialize random seed

	if (systemInit() == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	CSVManager& manager = CSVManager::getInstance();
	manager.setParseStrategy(ParseStrategyFactory::createStrategy(ParseStrategyFactory::CSV_format_t));

	// Load quotes from CSV files
	if (!manager.loadFile(QUOTES_FILE) || !manager.loadFile(WORDS_FILE))
	{
		std::cerr << "Could not load one or more files" << std::endl;
		return 1;
	}

	QuoteManager quoteManager(manager);

	// Interaction with the user
	std::cout << "How are you feeling today?" << std::endl;
	std::string line;
	std::getline(std::cin, line);

	// Check for happy words or sad words in the user's input
	WordDetector wordDetector(manager);
	std::string	 emotion = "Neutral";
	if (wordDetector.containsWord(WORDS_FILE, "happy_words", line))
	{
		std::cout << "You seem happy!" << std::endl;
		emotion = "sad_quotes";
	}
	else if (wordDetector.containsWord(WORDS_FILE, "sad_words", line))
	{
		std::cout << "You seem sad." << std::endl;
		emotion = "happy_quotes";
	}
	else
	{
		std::cout << "No specific emotion detected." << std::endl;
	}

	// if user is happy, get a random sad quote and vice versa
	std::string quote = quoteManager.getRandomQuote(QUOTES_FILE, emotion);
	std::cout << "Here is a quote for you: " << quote << std::endl;

	return 0;
}
