#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__


#include <iostream>
#include <memory>
#include <string>
#include <vector>


//bool HandleInput(int &input)
//{
//    std::cout << "what do you want to do?" << std::endl;
//    std::cout << "1. Get a quote" << std::endl;
//    std::cout << "2. Exit" << std::endl;
//    std::cout << "3. Get History" << std::endl;
//    std::cout << "4. Backup" << std::endl;
//    std::cout << "5. Restore" << std::endl;
//    std::cin >> input;

//    if (input >= 1 && input <= 5)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}


/**
 * @brief The State class represents a state in the state machine.
 */
class State
{
public:
    /**
	 * @brief Virtual destructor for the State class.
	 */
    virtual ~State() = default;

    /**
	 * @brief Pure virtual method to execute the state's behavior.
	 */
    virtual void execute() = 0;
};

/**
 * @brief The StateMachine class represents a simple state machine.
 */
class StateMachine
{
private:
    std::shared_ptr<State> currentState_; /**< The current state of the state machine. */

public:
    /**
	 * @brief Constructor for the StateMachine class.
	 * @param initialState The initial state of the state machine.
	 */
    StateMachine(std::shared_ptr<State> initialState) : currentState_(initialState)
    {
    }

    /**
	 * @brief Sets the current state of the state machine.
	 * @param state The new state to set.
	 */
    void setState(std::shared_ptr<State> state)
    {
        currentState_ = state;
    }

    /**
	 * @brief Executes the current state's behavior.
	 */
    void run()
    {
        currentState_->execute();
    }
};


#endif // __STATEMACHINE_H__