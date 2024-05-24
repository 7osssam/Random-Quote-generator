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

// Enum for representing different states
enum class StateType
{
	GetQuote,
	Exit,
	GetHistory,
	Backup,
	Restore
};

// State machine class to manage states
class StateMachine
{
private:
	std::shared_ptr<State> currentState_;

public:
	StateMachine(std::shared_ptr<State> initialState);

	void setState(std::shared_ptr<State> state);

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
	GetQuoteState();

	void execute() override;
};

class GetHistoryState : public State
{
private:
	QuoteManager& quoteManager_;

public:
	GetHistoryState();

	void execute() override;
};

class BackupState : public State
{
private:
	Caretaker caretaker;

public:
	BackupState() = default;

	void execute() override;
};

class RestoreState : public State
{
private:
	Caretaker caretaker;

public:
	RestoreState() = default;

	void execute() override;
};

class ExitState : public State
{
public:
	void execute() override;
};

#endif // __STATEMACHINE_H__
