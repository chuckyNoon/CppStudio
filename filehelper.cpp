#include "filehelper.h"
#include <string>
#include <fstream>
#include <sstream>

FileHelper::FileHelper()
{

}

std::string FileHelper::getFileContent(std::string filePath)
{
    std::ifstream file;
    file.open(filePath);
    if (file.is_open())
    {
        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();
        return buffer.str();
    }
    else
    {
        return "";
    }
}

void FileHelper::saveContentToFile(std::string filePath, std::string content)
{
    std::ofstream file;
    file.open(filePath);
    if (file.is_open())
    {
        file << content;
    }
}
