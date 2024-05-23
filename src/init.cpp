
#include "../inc/init.hpp"


static void LoadFiles(FilesManager &filesManager)
{
    filesManager.loadFile(FileManagerFactory::FileType::CSV, WORDS_FILE);
    filesManager.loadFile(FileManagerFactory::FileType::CSV, QUOTES_FILE);
}


// TODO: the output should be outputed in a log file
// look https://github.com/odundar/simple_cpp_logger/blob/master/Logger.hpp
/**
 * Initializes the system.
 * 
 * This function checks if the program is running from the expected build directory.
 * If not, it displays an error message and returns EXIT_FAILURE.
 * If the program is running from the build directory, it displays a success message and returns EXIT_SUCCESS.
 * 
 * @return Returns EXIT_SUCCESS if the program is running from the build directory, otherwise returns EXIT_FAILURE.
 */
bool systemInit()
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
        std::cerr << "ERROR: Please run the program from the build directory" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Running the program from the build directory" << std::endl;

    // loading files
    FilesManager filesManager;
    LoadFiles(filesManager);


    return EXIT_SUCCESS;
}