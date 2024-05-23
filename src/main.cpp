#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../inc/Backup.hpp"
#include "../inc/CSVManager.hpp"
#include "../inc/FileManagerFactory.hpp"
#include "../inc/FilesManager.hpp"
#include "../inc/QuoteManager.hpp"
#include "../inc/StateMachine.hpp"
#include "../inc/init.hpp"
#include "../inc/UserManager.hpp"

void displayMenu()
{
	std::cout << "\n";
	std::cout << "====================================\n";
	std::cout << "|          Quote Manager           |\n";
	std::cout << "====================================\n";
	std::cout << "|                                  |\n";
	std::cout << "|   What do you want to do?        |\n";
	std::cout << "|                                  |\n";
	std::cout << "|   1. Get a quote                 |\n";
	std::cout << "|   2. Exit                        |\n";
	std::cout << "|   3. Get History                 |\n";
	std::cout << "|   4. Backup                      |\n";
	std::cout << "|   5. Restore                     |\n";
	std::cout << "|                                  |\n";
	std::cout << "====================================\n";
	std::cout << "\n";
}

void displayError(const std::string& message)
{
	system("echo \033[31m");
	std::cerr << message << std::endl;
	system("echo \033[0m");
}

void displaySuccess(const std::string& message)
{
	system("echo \033[32m");
	std::cout << message << std::endl;
	system("echo \033[0m");
}

void displayInfo(const std::string& message)
{
	system("echo \033[33m");
	std::cout << message << std::endl;
	system("echo \033[0m");
}

StateType HandleInput(UserManager& userManager)
{
	displayMenu();
	int input;
	std::cin >> input;

	switch (input)
	{
		case 1:
			return StateType::GetQuote;
		case 2:
			return StateType::Exit;
		case 3:
			return StateType::GetHistory;
		case 4:
			if (userManager.verifyUser())
			{
				return StateType::Backup;
			}
			else
			{
				displayError("Password verification failed.");
				return HandleInput(userManager);
			}
		case 5:
			if (userManager.verifyUser())
			{
				return StateType::Restore;
			}
			else
			{
				displayError("Password verification failed.");
				return HandleInput(userManager);
			}
		default:
			displayError("Invalid choice. Please try again.");
			std::cin.clear();
			return HandleInput(userManager);
	}
}

int main()
{
	if (systemInit() == EXIT_FAILURE)
	{
		return EXIT_FAILURE;
	}

	UserManager userManager;
	if (userManager.isUsersEmpty())
	{
		//std::cout << "No users found. Creating a new user.\n";
		displayInfo("No users found. Creating a new user.");
		userManager.createUser();
	}
	else if (!userManager.verifyUser())
	{
		displayError("Password verification failed.");
		return EXIT_FAILURE;
	}

	std::shared_ptr<StateMachine> stateMachine =
		std::make_shared<StateMachine>(std::make_shared<GetQuoteState>());

	while (true)
	{
		StateType choice = HandleInput(userManager);

		switch (choice)
		{
			case StateType::GetQuote:
				stateMachine->setState(std::make_shared<GetQuoteState>());
				break;
			case StateType::Exit:
				stateMachine->setState(std::make_shared<ExitState>());
				break;
			case StateType::GetHistory:
				stateMachine->setState(std::make_shared<GetHistoryState>());
				break;
			case StateType::Backup:
				stateMachine->setState(std::make_shared<BackupState>());
				break;
			case StateType::Restore:
				stateMachine->setState(std::make_shared<RestoreState>());
				break;

			default:
				break;
		}

		stateMachine->run();
	}

	return 0;
}