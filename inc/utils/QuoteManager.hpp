#ifndef __QUOTEMANAGER_H__
#define __QUOTEMANAGER_H__

#include "FilesManager.hpp"

#include <algorithm>
#include <string>
#include <vector>

#define QUOTES_FILE "../data/Quotes.csv"

class QuoteManager
{
private:
	FilesManager			 filesManager_;
	std::vector<std::string> history_;
	QuoteManager();

	QuoteManager(const QuoteManager&) = delete;
	QuoteManager& operator=(const QuoteManager&) = delete;

public:
	// create singleton
	static QuoteManager& getInstance();
	std::string			 getRandomQuote(const std::string& emotion);

	std::vector<std::string> getHistory() const;
	void					 setHistory(const std::vector<std::string>& history);
};

#endif // __QUOTEMANAGER_H__