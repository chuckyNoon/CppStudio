#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <string>

class FileHelper
{
public:
    FileHelper();
    static std::string getFileContent(std::string filePath);
    static void saveContentToFile(std::string filePath, std::string content);
};

#endif // FILEHELPER_H
