#include "FilesManager.hpp"

FilesManager::FilesManager(FileManagerFactory::FileType type) :
	manager_(FileManagerFactory::createFileManager(type))
{
}

bool FilesManager::loadFile(const std::string& filename) const
{
	return manager_->loadFile(filename);
}

std::vector<std::string> FilesManager::getData(const std::string& filename, const std::string& key) const
{
	return manager_->getData(filename, key);
}

void FilesManager::setData(const std::string& filename, const std::string& key,
						   const std::vector<std::string>& data) const
{
	manager_->setData(filename, key, data);
}

bool FilesManager::resetData(const std::string& filename) const
{
	return manager_->resetData(filename);
}

bool FilesManager::saveFile(const std::string& filename) const
{
	return manager_->saveFile(filename);
}

FilesManager::~FilesManager()
{
	// Do not delete manager_ as it is a singleton instance managed elsewhere
}