#include "../inc/FilesManager.hpp"


bool FilesManager::loadFile(FileManagerFactory::FileType type, const std::string &filename) const
{
    FileManager *manager = FileManagerFactory::createFileManager(type);
    return manager->loadFile(filename);
}

std::vector<std::string> FilesManager::getData(FileManagerFactory::FileType type,
                                               const std::string &filename,
                                               const std::string &key) const
{
    FileManager *manager = FileManagerFactory::createFileManager(type);
    return manager->getData(filename, key);
}

void FilesManager::setData(FileManagerFactory::FileType type,
                           const std::string &filename,
                           const std::string &key,
                           const std::vector<std::string> &data) const
{
    FileManager *manager = FileManagerFactory::createFileManager(type);
    manager->setData(filename, key, data);
}

bool FilesManager::resetData(FileManagerFactory::FileType type, const std::string &filename) const
{
    FileManager *manager = FileManagerFactory::createFileManager(type);
    return manager->resetData(filename);
}

bool FilesManager::saveFile(FileManagerFactory::FileType type, const std::string &filename) const
{
    FileManager *manager = FileManagerFactory::createFileManager(type);
    return manager->saveFile(filename);
}