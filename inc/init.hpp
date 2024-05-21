#ifndef __INIT_H__
#define __INIT_H__

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

#define WORDS_FILE "../data/Words.csv"
#define QUOTES_FILE "../data/Quotes.csv"
#define BACKUP_FILE "../data/backup.txt"
#define BUILD_DIR "../build"

// TODO: the output should be outputed in a log file
// look https://github.com/odundar/simple_cpp_logger/blob/master/Logger.hpp
bool systemInit()
{
    // Get the current path
    std::filesystem::path currentPath = std::filesystem::current_path();
    std::cout << "Current path is " << currentPath << '\n';

    // Define the expected build directory path
    std::filesystem::path buildDirectory = "../build";
    std::filesystem::path fullBuildPath = std::filesystem::absolute(buildDirectory);

    std::cout << "Expected build directory path is " << fullBuildPath << '\n';

    // Check if the program is running from the build directory
    if (currentPath != fullBuildPath)
    {
        std::cerr << "Please run the program from the build directory" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Running the program from the build directory" << std::endl;

    return EXIT_SUCCESS;
}

#endif // __INIT_H__