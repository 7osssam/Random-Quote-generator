#ifndef __BACKUP_H__
#define __BACKUP_H__

#include "FilesManager.hpp"
#include "QuoteManager.hpp"
#include <vector>

// Memento class
class Memento
{
private:
	std::vector<std::string> history_;

public:
	Memento(const std::vector<std::string>& history);
	std::vector<std::string> getHistory() const;
};

// Caretaker class
class Caretaker
{
private:
	std::unique_ptr<Memento> memento_;
	FilesManager			 filesManager_;
	QuoteManager&			 quoteManager_;

public:
	Caretaker();

	bool backup();
	bool restore();
};

#endif // __BACKUP_H__