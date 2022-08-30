#include "projectstorage.h"
#include "filehelper.h"
#include <filesystem>
#include <sstream>

ProjectStorage::ProjectStorage(ProjectConfig *_config)
{
    this->config = _config;
}

void ProjectStorage::setupFiles()
{
    if (!std::filesystem::exists(this->config->path.toStdString())){
        generateDefaultDirectory();
    }
}

void ProjectStorage::addNewFile()
{
    // to implement
}

void ProjectStorage::removeFile()
{
    // to implement
}

void ProjectStorage::getFiles()
{
    // to implement
}

void ProjectStorage::updateFile()
{
    // to implement
}

void ProjectStorage::generateDefaultDirectory()
{
    QString projectPath = this->config->path;
    QString projectName = this->config->name;
    std::filesystem::create_directory(projectPath.toStdString());

    const char *mainCppDefaultContent = R"""(#include <iostream>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
    )""";

    std::stringstream cmakeSstream;
    cmakeSstream << "cmake_minimum_required(VERSION 3.5)\n\n";
    cmakeSstream << "project(testt LANGUAGES CXX)\n\n";
    cmakeSstream << "set(CMAKE_CXX_STANDARD 17)\n\n";
    cmakeSstream << "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n";
    cmakeSstream << "add_executable(" << projectName.toStdString() << " main.cpp)\n";
    cmakeSstream << "install(TARGETS " << projectName.toStdString() << "\n";
    cmakeSstream << "LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})";

    FileHelper::saveContentToFile(projectPath.toStdString() + "\\main.cpp", mainCppDefaultContent);
    FileHelper::saveContentToFile(projectPath.toStdString() + "\\CMakeLists.txt", cmakeSstream.str().c_str());
}

QString ProjectStorage::getMainCpp()
{
    std::string stdStr = FileHelper::getFileContent(this->config->path.toStdString() + "\\main.cpp");
    return QString::fromStdString(stdStr);
}

void ProjectStorage::updateMainCpp(QString newContent)
{
    FileHelper::saveContentToFile(this->config->path.toStdString() + "\\main.cpp", newContent.toStdString());
}


