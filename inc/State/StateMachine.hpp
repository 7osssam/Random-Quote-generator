#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Backup.hpp"
#include "QuoteManager.hpp"
#include "WordDetector.hpp"

/**
 * @brief The base class for all states in the state machine.
 */
class State
{
public:
	virtual ~State() = default;
	virtual void execute() = 0;
};

/**
 * @brief Represents a state machine that manages different states.
 *
 * The StateMachine class is responsible for managing different states and transitioning between them.
 * It provides functionality to set the current state, execute the current state, and drive the state machine.
 */
class StateMachine
{
private:
	std::shared_ptr<State> currentState_;

public:
	// Enum for representing different states
	enum class StateType
	{
		GetQuote,	/**< The state for getting a quote based on the user's emotion. */
		Exit,		/**< The state for exiting the program. */
		GetHistory, /**< The state for getting the history of quotes. */
		Backup,		/**< The state for creating a backup of the quote history. */
		Restore		/**< The state for restoring the quote history from a backup. */
	};

	/**
	 * @brief Constructs a new StateMachine object with the given initial state.
	 *
	 * @param initialState The initial state of the state machine.
	 */
	StateMachine(std::shared_ptr<State> initialState);

	/**
	 * @brief Sets the current state of the StateMachine.
	 *
	 * This function sets the current state of the StateMachine to the specified state.
	 *
	 * @param state The state to set as the current state.
	 */
	void setState(std::shared_ptr<State> state);

	/**
	 * @brief Executes the current state of the state machine.
	 *
	 * This function executes the current state of the state machine by calling its execute function.
	 * It is responsible for driving the state machine and transitioning between states.
	 */
	void run();
};

/**
 * @class GetQuoteState
 * @brief Represents a state in the state machine that retrieves a random quote based on the user's current emotion.
 * 
 * This state is responsible for prompting the user for their current emotion, detecting the emotion based on the input,
 */
class GetQuoteState : public State
{
private:
	std::string	  line{};		 /**< The current line of text. */
	std::string	  quote{};		 /**< The random quote. */
	std::string	  emotion{};	 /**< The user's current emotion. */
	QuoteManager& quoteManager_; /**< The singleton instance of the QuoteManager class. */
	WordDetector& wordDetector_; /**< The singleton instance of the WordDetector class. */

public:
	/**
	 * @brief Constructs a new instance of the GetQuoteState class.
	 * 
	 * This constructor initializes the GetQuoteState object by obtaining the singleton instances of the QuoteManager and WordDetector classes.
	 */
	GetQuoteState();

	/**
	 * @brief Executes the GetQuoteState.
	 * 
	 * This function prompts the user for their current emotion, detects the emotion based on the input,
	 * and retrieves a random quote based on the detected emotion.
	 */
	void execute() override;
};

/**
 * @class GetHistoryState
 * @brief Represents the state for retrieving and printing the history quotes.
 * 
 * This state is responsible for printing the history quotes stored in the quote manager.
 */
class GetHistoryState : public State
{
private:
	QuoteManager& quoteManager_; /**< The singleton instance of the QuoteManager class. */

public:
	/**
	 * @brief Constructor for the GetHistoryState class.
	 * 
	 * Initializes the quoteManager_ member variable with the instance of the QuoteManager singleton.
	 */
	GetHistoryState();

	/**
	 * @brief Executes the GetHistoryState.
	 *
	 * This function is responsible for printing the history quotes stored in the quote manager.
	 */
	void execute() override;
};

/**
 * @class BackupState
 * @brief Represents the state for creating a backup of the current state of the quote manager.
 * 
 * This state is responsible for creating a backup of the current state of the quote manager.
 */
class BackupState : public State
{
private:
	Caretaker caretaker; /**< The caretaker object used to manage the memento objects. */

public:
	/**
	 * @brief Executes the backup operation for the current state.
	 * 
	 * This function calls the `backup` method of the `caretaker` object, passing the `quoteManager_` as a parameter.
	 * The `backup` method is responsible for creating a backup of the current state of the `quoteManager_`.
	 * 
	 * @note backup is designed to be a part of the Memento design pattern.
	 */
	void execute() override;
};

/**
 * @class RestoreState
 * @brief Represents the state for restoring the state of the quote manager.
 * 
 * This state is responsible for restoring the state of the quote manager from a backup.
 * @embed{diagram_hierarchy_class.svg}
 */
class RestoreState : public State
{
private:
	Caretaker caretaker; /**< The caretaker object used to manage the memento objects. */

public:
	/**
	 * @brief Executes the restore state operation.
	 * 
	 * This function restores the state of the quote manager by using the caretaker object.
	 * The caretaker object is responsible for managing the memento objects and restoring the state of the quote manager.
	 */
	void execute() override;
};

/**
 * @class ExitState
 * @brief Represents the exit state of the state machine.
 * 
 * The ExitState class is a derived class of the State class. It is responsible for terminating the program with a successful exit status.
 */
class ExitState : public State
{
public:
	/**
	 * @brief Executes the exit state of the state machine.
	 * 
	 * This function is responsible for terminating the program with a successful exit status.
	 */
	void execute() override;
};

#endif // __STATEMACHINE_H__
