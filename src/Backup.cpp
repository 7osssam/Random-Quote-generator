#include "../inc/Backup.hpp"

#define BACKUP_FILE "../data/backup.txt"

Memento::Memento(const std::vector<std::string>& history) : history_(history)
{
}
std::vector<std::string> Memento::getHistory() const
{
	return history_;
}

Caretaker::Caretaker() :
	filesManager_{FileManagerFactory::FileType::Text}, quoteManager_{QuoteManager::getInstance()}
{
}

bool Caretaker::backup()
{
	memento_ = std::make_unique<Memento>(quoteManager_.getHistory());

	if (!filesManager_.loadFile(BACKUP_FILE))
	{
		return false;
	}

	filesManager_.setData(BACKUP_FILE, "", quoteManager_.getHistory());

	// using TextManager
	filesManager_.saveFile(BACKUP_FILE);

	return true;
}
bool Caretaker::restore()
{
	if (!filesManager_.loadFile(BACKUP_FILE))
	{
		return false;
	}

	auto history = filesManager_.getData(BACKUP_FILE, "");

	if (history.empty())
	{
		return false;
	}

	quoteManager_.setHistory(history);

	return true;
}