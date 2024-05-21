#include "../inc/FileManagerFactory.hpp"


FileManager *FileManagerFactory::createFileManager(FileType type)
{
    switch (type)
    {
    case FileType::CSV:
        return &CSVManager::getInstance();
    case FileType::Text:
        return &TextFileManager::getInstance();
    default:
        throw std::invalid_argument("Unknown file type");
    }
}