#include "../inc/StateMachine.hpp"
#include "../inc/QuoteManager.hpp"
#include "../inc/init.hpp"

#define HAPPY_WORDS	 "happy_words"
#define SAD_WORDS	 "sad_words"

#define HAPPY_QUOTES "happy_quotes"
#define SAD_QUOTES	 "sad_quotes"

StateMachine::StateMachine(std::shared_ptr<State> initialState) : currentState_(initialState)
{
}

/**
 * @brief Sets the current state of the StateMachine.
 *
 * This function sets the current state of the StateMachine to the specified state.
 *
 * @param state The state to set as the current state.
 */
void StateMachine::setState(std::shared_ptr<State> state)
{
	currentState_ = state;
}

/**
 * @brief Executes the current state of the state machine.
 *
 * This function executes the current state of the state machine by calling its execute function.
 * It is responsible for driving the state machine and transitioning between states.
 */
void StateMachine::run()
{
	currentState_->execute();
}

GetQuoteState::GetQuoteState() :
	quoteManager_(QuoteManager::getInstance()), wordDetector_(WordDetector::getInstance())
{
}
/**
 * @brief Executes the GetQuoteState.
 * 
 * This function prompts the user for their current emotion, detects the emotion based on the input,
 * and retrieves a random quote based on the detected emotion.
 */
void GetQuoteState::execute()
{
	std::cout << "How are you feeling today?" << std::endl;
	std::cin.ignore();
	std::getline(std::cin, line);

	if (wordDetector_.containsWord(HAPPY_WORDS, line))
	{
		std::cout << "You seem happy!" << std::endl;
		emotion = SAD_QUOTES;
	}
	else if (wordDetector_.containsWord(SAD_WORDS, line))
	{
		std::cout << "You seem sad." << std::endl;
		emotion = HAPPY_QUOTES;
	}
	else
	{
		std::cout << "No specific emotion detected." << std::endl;
	}

	quote = quoteManager_.getRandomQuote(emotion);
	std::cout << "Here is a quote for you: " << quote << std::endl;
}

GetHistoryState::GetHistoryState() : quoteManager_(QuoteManager::getInstance())
{
}

/**
 * @brief Executes the GetHistoryState.
 *
 * This function is responsible for printing the history quotes stored in the quote manager.
 */
void GetHistoryState::execute()
{
	for (const auto& historyQuote: quoteManager_.getHistory())
	{
		std::cout << historyQuote << std::endl;
	}
}

/**
 * @brief Executes the backup operation for the current state.
 * 
 * This function calls the `backup` method of the `caretaker` object, passing the `quoteManager_` as a parameter.
 * The `backup` method is responsible for creating a backup of the current state of the `quoteManager_`.
 * 
 * @note backup is designed to be a part of the Memento design pattern.
 */
void BackupState::execute()
{
	caretaker.backup();
	std::cout << "Backup completed successfully." << std::endl;
}

/**
 * @brief Executes the restore state operation.
 * 
 * This function restores the state of the quote manager by using the caretaker object.
 * The caretaker object is responsible for managing the memento objects and restoring the state of the quote manager.
 */
void RestoreState::execute()
{
	if (caretaker.restore())
	{
		std::cout << "Restore completed successfully." << std::endl;
	}
	else
	{
		std::cout << "Restore failed." << std::endl;
	}
}

/**
 * @brief Executes the exit state of the state machine.
 * 
 * This function is responsible for terminating the program with a successful exit status.
 */
void ExitState::execute()
{
	exit(EXIT_SUCCESS);
}