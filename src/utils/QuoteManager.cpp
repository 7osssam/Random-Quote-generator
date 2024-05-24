#include "QuoteManager.hpp"

QuoteManager::QuoteManager() : filesManager_{FileManagerFactory::FileType::CSV}
{
	filesManager_.loadFile(QUOTES_FILE);
}

QuoteManager& QuoteManager::getInstance()
{
	static QuoteManager instance;
	return instance;
}

std::string QuoteManager::getRandomQuote(const std::string& emotion)
{
	//auto quotes = csvManager_.getData(filename, emotion);
	auto quotes = filesManager_.getData(QUOTES_FILE, emotion);
	if (!quotes.empty())
	{
		int index = rand() % quotes.size();

		// Add the quote to the history
		history_.push_back(quotes[index]);

		return quotes[index];
	}
	return "No quotes available for this emotion.";
}

std::vector<std::string> QuoteManager::getHistory() const
{
	return history_;
}

void QuoteManager::setHistory(const std::vector<std::string>& history)
{
	history_ = history;
}