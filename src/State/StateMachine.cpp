#include "StateMachine.hpp"
#include "QuoteManager.hpp"

#define HAPPY_WORDS	 "happy_words"
#define SAD_WORDS	 "sad_words"

#define HAPPY_QUOTES "happy_quotes"
#define SAD_QUOTES	 "sad_quotes"

#include "SystemMenu.hpp"

StateMachine::StateMachine(std::shared_ptr<State> initialState) : currentState_(initialState)
{
}

void StateMachine::setState(std::shared_ptr<State> state)
{
	currentState_ = state;
}

void StateMachine::run()
{
	currentState_->execute();
}

GetQuoteState::GetQuoteState() :
	quoteManager_(QuoteManager::getInstance()), wordDetector_(WordDetector::getInstance())
{
}

void GetQuoteState::execute()
{
	displayInfo("How are you feeling today?");
	std::cin.ignore();
	std::getline(std::cin, line);

	if (wordDetector_.containsWord(HAPPY_WORDS, line))
	{
		displayInfo("You seem happy! :)");
		emotion = SAD_QUOTES;
	}
	else if (wordDetector_.containsWord(SAD_WORDS, line))
	{
		displayInfo("You seem sad. :(");
		emotion = HAPPY_QUOTES;
	}
	else
	{
		displayError("No specific emotion detected. -_-");
	}

	quote = quoteManager_.getRandomQuote(emotion);
	std::cout << "Here is a quote for you: " << quote << std::endl;
}

GetHistoryState::GetHistoryState() : quoteManager_(QuoteManager::getInstance())
{
}

void GetHistoryState::execute()
{
	std::cout << "History Quotes:" << std::endl;
	std::cout << "----------------" << std::endl;
	for (const auto& historyQuote: quoteManager_.getHistory())
	{
		std::cout << historyQuote << std::endl;
		std::cout << "----------------" << std::endl;
	}
}

void BackupState::execute()
{
	if (caretaker.backup())
	{
		displaySuccess("Backup completed successfully.");
	}
	else
	{
		displayError("Backup failed.");
	}
}

void RestoreState::execute()
{
	if (caretaker.restore())
	{
		displaySuccess("Restore completed successfully.");
	}
	else
	{
		displayError("Restore failed.");
	}
}

void ExitState::execute()
{
	displaySuccess("Exiting the program.");
	exit(EXIT_SUCCESS);
}