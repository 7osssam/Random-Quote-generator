#ifndef __INIT_H__
#define __INIT_H__

#include "FilesManager.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define WORDS_FILE	"../data/Words.csv"
#define QUOTES_FILE "../data/Quotes.csv"
#define BACKUP_FILE "../data/backup.txt"
#define BUILD_DIR	"../build"

// TODO: the output should be outputed in a log file
// look https://github.com/odundar/simple_cpp_logger/blob/master/Logger.hpp
bool systemInit();

#endif // __INIT_H__