#include "../inc/CSVManager.hpp"

CSVManager& CSVManager::getInstance(void)
{
	static CSVManager instance;
	return instance;
}

bool CSVManager::loadFile(const std::string& filename)
{
	std::lock_guard<std::mutex> lock(mutex_);
	std::ifstream				file(filename);
	//std::ifstream file(filename, std::ios::in | std::ios::binary);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return false;
	}

	filename_ = filename;

	std::string line;
	if (std::getline(file, line))					// Read header
	{
		auto headers = parseStrategy_->parse(line); // Get headers

		// Initialize data map for this file
		data_[filename] = {};

		for (const auto& header: headers)
		{
			data_[filename][header] = {};
		}

		// Read data rows

		auto& fileData = data_[filename];

		std::string currentHeader;
		std::string currentValue;

		while (std::getline(file, line))
		{
			auto values = parseStrategy_->parse(line); // Parse values

			for (size_t i = 0; i < headers.size(); ++i)
			{
				//add temp variables for readability

				if (i < values.size())
				{
					currentHeader = headers[i];
					currentValue = values[i];
					fileData[currentHeader].push_back(currentValue); // Store values
				}
				else
				{
					currentHeader = headers[i];
					fileData[currentHeader].push_back(""); // Add empty value if missing
				}
			}
		}
	}
	else
	{
		std::cerr << "Empty file: " << filename << std::endl;
		return false;
	}

	return true;
}

std::vector<std::string> CSVManager::getData(const std::string& filename, const std::string& column)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (data_.find(filename) != data_.end())
	{
		if (data_[filename].find(column) != data_[filename].end())
		{
			return data_[filename][column];
		}
	}

	return {};
}

void CSVManager::setData(const std::string& filename, const std::string& column,
						 const std::vector<std::string>& data)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (data_.find(filename) != data_.end())
	{
		// If the column doesn't exist in the data for the filename, create it
		if (data_[filename].find(column) == data_[filename].end())
		{
			data_[filename][column] = std::vector<std::string>();
		}

		// Set the data for the column
		data_[filename][column] = data;
	}
	else
	{
		// If the filename doesn't exist in the data, create it and add the column
		data_[filename] = std::map<std::string, std::vector<std::string>>();
		data_[filename][column] = data;
	}
}

bool CSVManager::resetData(const std::string& filename)
{
	std::lock_guard<std::mutex> lock(mutex_);
	if (data_.find(filename) != data_.end())
	{
		data_.erase(filename);
		return true;
	}
	return false;
}

bool CSVManager::saveFile(const std::string& filename) const
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filename << std::endl;
		return false;
	}

	if (!data_.empty())
	{
		// Write headers
		auto& headers = data_.at(filename);
		for (auto it = headers.begin(); it != headers.end(); ++it)
		{
			file << it->first;
			if (std::next(it) != headers.end())
			{
				file << ",";
			}
		}
		file << "\n";

		// Write data rows
		size_t numRows = headers.begin()->second.size();
		for (size_t i = 0; i < numRows; ++i)
		{
			for (auto it = headers.begin(); it != headers.end(); ++it)
			{
				if (i < it->second.size())
				{
					file << it->second[i];
				}
				if (std::next(it) != headers.end())
				{
					file << ",";
				}
			}
			file << "\n";
		}
	}
	else
	{
		return false;
	}
	return true;
}
