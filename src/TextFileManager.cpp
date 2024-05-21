#include "../inc/TextFileManager.hpp"


TextFileManager &TextFileManager::getInstance(void)
{
    static TextFileManager instance;
    return instance;
}


bool TextFileManager::loadFile(const std::string &filename)
{
    std::lock_guard<std::mutex> lock(mutex_);
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    filename_ = filename;

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line))
    {
        lines.push_back(line);
    }
    data_[filename] = lines;

    return true;
}

std::vector<std::string> TextFileManager::getData(const std::string &filename, const std::string &key)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (data_.find(filename) != data_.end())
    {
        return data_[filename];
    }
    return {};
}

void TextFileManager::setData(const std::string &filename, const std::string &key, const std::vector<std::string> &data)
{
    std::lock_guard<std::mutex> lock(mutex_);
    //data_[filename] = data;

    // this function should append the data to the file
    if (data_.find(filename) != data_.end())
    {
        data_[filename].insert(data_[filename].end(), data.begin(), data.end());
    }
    else
    {
        data_[filename] = data;
    }
}

bool TextFileManager::resetData(const std::string &filename)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (data_.find(filename) != data_.end())
    {
        data_[filename].clear();
        return true;
    }
    return false;
}

bool TextFileManager::saveFile(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    if (data_.find(filename) != data_.end())
    {
        const auto &lines = data_.at(filename);
        for (const auto &line : lines)
        {
            file << line << "\n";
        }
    }
    else
    {
        return false;
    }
    return true;
}