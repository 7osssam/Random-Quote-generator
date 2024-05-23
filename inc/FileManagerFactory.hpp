#ifndef __FILEMANAGERFACTORY_H__
#define __FILEMANAGERFACTORY_H__

#include "CSVManager.hpp"
#include "FileManager.hpp"
#include "TextManager.hpp"
#include <stdexcept>

/**
 * @brief The FileManagerFactory class is responsible for creating instances of FileManager based on the specified FileType.
 * @note This class follows the Factory Method design pattern.
 */
class FileManagerFactory
{
public:
    /**
	 * @brief The FileType enum class represents the type of file to be managed by the FileManager.
	 */
    enum class FileType
    {
        CSV,  /**< Comma-Separated Values file type */
        Text, /**< Text file type */
              // TODO: JSON
    };

    /**
	 * @brief createFileManager creates a FileManager instance based on the specified FileType.
	 * @param type The FileType of the file to be managed.
	 * @return A pointer to the created FileManager instance.
	 */
    static FileManager *createFileManager(FileType type);
};

#endif // __FILEMANAGERFACTORY_H__
