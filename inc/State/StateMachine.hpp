#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Backup.hpp"
#include "QuoteManager.hpp"
#include "WordDetector.hpp"

// Abstract base class for states
class State
{
public:
	virtual ~State() = default;
	virtual void execute() = 0;
};

// State machine class to manage states
class StateMachine
{
private:
	std::shared_ptr<State> currentState_;

public:
	// Enum for representing different states
	enum class StateType
	{
		GetQuote,
		Exit,
		GetHistory,
		Backup,
		Restore
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

// Concrete state classes
class GetQuoteState : public State
{
private:
	std::string	  line{};
	std::string	  quote{};
	std::string	  emotion{};
	QuoteManager& quoteManager_;
	WordDetector& wordDetector_;

public:
	/**
	 * @brief Constructs a new instance of the GetQuoteState class.
	 * 
	 * This constructor initializes the GetQuoteState object by obtaining the singleton instances of the QuoteManager and WordDetector classes.
	 * 
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

class GetHistoryState : public State
{
private:
	QuoteManager& quoteManager_;

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

class BackupState : public State
{
private:
	Caretaker caretaker;

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

class RestoreState : public State
{
private:
	Caretaker caretaker;

public:
	/**
	 * @brief Executes the restore state operation.
	 * 
	 * This function restores the state of the quote manager by using the caretaker object.
	 * The caretaker object is responsible for managing the memento objects and restoring the state of the quote manager.
	 */
	void execute() override;
};

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
