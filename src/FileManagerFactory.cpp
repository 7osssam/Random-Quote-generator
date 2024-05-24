#include "../inc/FileManagerFactory.hpp"

FileManager* FileManagerFactory::createFileManager(FileType type)
{
	switch (type)
	{
		case FileType::CSV:
			return &CSVManager::getInstance();
		case FileType::Text:
			return &TextManager::getInstance();
		default:
			throw std::invalid_argument("Unknown file type");
	}
}