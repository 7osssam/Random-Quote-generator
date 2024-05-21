#ifndef __QUOTEMANAGER_H__
#define __QUOTEMANAGER_H__


#include "CSVManager.hpp"
#include <algorithm>
#include <string>
#include <vector>

class QuoteManager
{
private:
    CSVManager &csvManager_;
    std::vector<std::string> history_;

public:
    QuoteManager(CSVManager &csvManager) : csvManager_(csvManager)
    {
    }

    std::string getRandomQuote(const std::string &filename, const std::string &emotion)
    {
        auto quotes = csvManager_.getData(filename, emotion);
        if (!quotes.empty())
        {
            int index = rand() % quotes.size();

            // Add the quote to the history
            history_.push_back(quotes[index]);

            return quotes[index];
        }
        return "No quotes available for this emotion.";
    }

    // get the history
    std::vector<std::string> getHistory() const
    {
        return history_;
    }

    // set the history
    void setHistory(const std::vector<std::string> &history)
    {
        history_ = history;
    }
};

class WordDetector
{
private:
    CSVManager &csvManager_;

    std::vector<std::string> split(const std::string &s, char delimiter)
    {
        std::vector<std::string> words;
        std::stringstream ss(s);
        std::string word;

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
    WordDetector(CSVManager &csvManager) : csvManager_(csvManager)
    {
    }

    bool containsWord(const std::string &filename, const std::string &emotion, const std::string &line)
    {
        bool result = false;
        auto words = csvManager_.getData(filename, emotion);

        //split the line into words
        std::vector<std::string> lineWords = split(line, ' ');

        // search in a line a word from the words vector
        for (const auto &word : words)
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

#endif // __QUOTEMANAGER_H__