#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "StateMachine.hpp"
#include "SystemMenu.hpp"
#include "UserManager.hpp"

/**
 * @brief Handles user input and returns the corresponding state of the state machine.
 * 
 * @param userManager The user manager object.
 * @return The state of the state machine based on user input.
 */
StateMachine::StateType HandleInput(UserManager& userManager)
{
	displayMenu();
	int input;
	std::cin >> input;

	switch (input)
	{
		case 1:
			return StateMachine::StateType::GetQuote;
		case 2:
			return StateMachine::StateType::Exit;
		case 3:
			return StateMachine::StateType::GetHistory;
		case 4:
			if (userManager.verifyUser())
			{
				return StateMachine::StateType::Backup;
			}
			else
			{
				displayError("Password verification failed.");
				return HandleInput(userManager); // Recursively call HandleInput to get a valid choice
			}
		case 5:
			if (userManager.verifyUser())
			{
				return StateMachine::StateType::Restore;
			}
			else
			{
				displayError("Password verification failed.");
				return HandleInput(userManager); // Recursively call HandleInput to get a valid choice
			}
		default:
			displayError("Invalid choice. Please try again.");
			std::cin.clear();
			return HandleInput(userManager); // Recursively call HandleInput to get a valid choice
	}
}

int main(void)
{
	if (systemInit() == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	UserManager userManager;
	bool		isUsersFileEmpty = userManager.isUsersEmpty();
	// Check if the users file is empty
	if (isUsersFileEmpty == true)
	{
		displayInfo("Creating a new user.");
		userManager.createUser(); // Create a new user
	}
	else
	{
		displayInfo("User found, please Enter username and password to verify.");
		if (!userManager.verifyUser()) // Verify the user's password
		{
			displayError("Password verification failed.");
			return EXIT_FAILURE;	   // Exit the program if password verification fails
		}
	}

	std::shared_ptr<StateMachine> stateMachine =
		std::make_shared<StateMachine>(std::make_shared<GetQuoteState>());

	while (true)
	{
		StateMachine::StateType choice = HandleInput(userManager);

		switch (choice)
		{
			case StateMachine::StateType::GetQuote:
				stateMachine->setState(std::make_shared<GetQuoteState>());
				break;
			case StateMachine::StateType::Exit:
				stateMachine->setState(std::make_shared<ExitState>());
				break;
			case StateMachine::StateType::GetHistory:
				stateMachine->setState(std::make_shared<GetHistoryState>());
				break;
			case StateMachine::StateType::Backup:
				stateMachine->setState(std::make_shared<BackupState>());
				break;
			case StateMachine::StateType::Restore:
				stateMachine->setState(std::make_shared<RestoreState>());
				break;

			default:
				break;
		}

		stateMachine->run();
	}

	return 0;
}