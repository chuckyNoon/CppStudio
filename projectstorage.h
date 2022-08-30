#ifndef PROJECTSTORAGE_H
#define PROJECTSTORAGE_H


#include "projectconfig.h"
#include <QString>

class ProjectStorage
{
public:
    ProjectStorage(ProjectConfig *config);
    void setupFiles();
    void addNewFile();
    void removeFile();
    void getFiles();
    QString getMainCpp(); // replace
    void updateMainCpp(QString newContent); // replace
    void updateFile();
private:
    void generateDefaultDirectory();
    ProjectConfig *config;
};

#endif // PROJECTSTORAGE_H
