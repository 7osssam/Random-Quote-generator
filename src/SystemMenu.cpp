
#include <thread>
#include <iostream>
// file system
#include <filesystem>

#include "SystemMenu.hpp"

#define COLOR_RED_COMMAND	 ("echo \033[31m")
#define COLOR_GREEN_COMMAND	 ("echo \033[32m")
#define COLOR_YELLOW_COMMAND ("echo \033[33m")
#define COLOR_RESET_COMMAND	 ("echo \033[0m")

// TODO: the output should be outputed in a log file
// look https://github.com/odundar/simple_cpp_logger/blob/master/Logger.hpp
bool systemInit(void)
{
	// Get the current path
	std::filesystem::path currentPath = std::filesystem::current_path();
	//std::cout << "Current path is " << currentPath << '\n';

	// Define the expected build directory path
	std::filesystem::path buildDirectory = "../build";
	std::filesystem::path fullBuildPath = std::filesystem::absolute(buildDirectory);

	//std::cout << "Expected build directory path is " << fullBuildPath << '\n';

	// Check if the program is running from the build directory
	if (currentPath != fullBuildPath)
	{
		displayError("Please run the program from the build directory.");
		return EXIT_FAILURE;
	}

	displaySuccess("Running the program from the build directory");

	return EXIT_SUCCESS;
}

void displayMenu(void)
{
	system(COLOR_YELLOW_COMMAND);
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
	system(COLOR_RESET_COMMAND);
}

void displayError(const std::string& message)
{
	system(COLOR_RED_COMMAND);
	std::cerr << message << std::endl;
	system(COLOR_RESET_COMMAND);
}

void displaySuccess(const std::string& message)
{
	system(COLOR_GREEN_COMMAND);
	std::cout << message << std::endl;
	system(COLOR_RESET_COMMAND);
}

void displayInfo(const std::string& message)
{
	system(COLOR_YELLOW_COMMAND);
	std::cout << message << std::endl;
	system(COLOR_RESET_COMMAND);
}
