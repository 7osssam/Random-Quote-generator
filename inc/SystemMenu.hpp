#ifndef __SYSTEMMENU_H__
#define __SYSTEMMENU_H__

/**
 * Initializes the system.
 * 
 * This function checks if the program is running from the expected build directory.
 * If not, it displays an error message and returns EXIT_FAILURE.
 * If the program is running from the build directory, it displays a success message and returns EXIT_SUCCESS.
 * 
 * @return Returns EXIT_SUCCESS if the program is running from the build directory, otherwise returns EXIT_FAILURE.
 */
bool systemInit(void);

/**
 * Displays the menu options to the user.
 */
void displayMenu(void);

/**
 * Displays an error message in red text.
 *
 * @param message The error message to be displayed.
 */
void displayError(const std::string& message);

/**
 * Displays a success message in green text.
 *
 * @param message The success message to be displayed.
 */
void displaySuccess(const std::string& message);

/**
 * Displays an information message in yellow text.
 *
 * @param message The message to be displayed.
 */
void displayInfo(const std::string& message);

#endif // __SYSTEMMENU_H__