#ifndef __BACKUP_H__
#define __BACKUP_H__


#include "FilesManager.hpp"
#include "QuoteManager.hpp"
#include "TextFileManager.hpp"
#include "init.hpp"
#include <memory>
#include <vector>


// Memento class
class Memento
{
private:
    std::vector<std::string> history_;

public:
    Memento(const std::vector<std::string> &history) : history_(history)
    {
    }
    std::vector<std::string> getHistory() const
    {
        return history_;
    }
};

// Caretaker class
class Caretaker
{
private:
    std::unique_ptr<Memento> memento_;
    FilesManager filesManager;

public:
    bool backup(QuoteManager &quoteManager)
    {
        memento_ = std::make_unique<Memento>(quoteManager.getHistory());

        if (!filesManager.loadFile(FileManagerFactory::FileType::Text, BACKUP_FILE))
        {
            return false;
        }

        filesManager.setData(FileManagerFactory::FileType::Text, BACKUP_FILE, "history", quoteManager.getHistory());


        // using TextFileManager
        filesManager.saveFile(FileManagerFactory::FileType::Text, BACKUP_FILE);

        return true;
    }
    bool restore(QuoteManager &quoteManager)
    {
        if (!filesManager.loadFile(FileManagerFactory::FileType::Text, BACKUP_FILE))
        {
            return false;
        }

        auto history = filesManager.getData(FileManagerFactory::FileType::Text, BACKUP_FILE, "history");

        if (history.empty())
        {
            return false;
        }

        quoteManager.setHistory(history);

        return true;
    }
};


#endif // __BACKUP_H__