#ifndef PROJECTCONFIG_H
#define PROJECTCONFIG_H


#include <QString>


class ProjectConfig
{
public:
    ProjectConfig(
        QString _name,
        QString _parentPath,
        QString _cmakePath,
        QString _compilerPath
        )
    {
        path = _parentPath + "\\" +_name ;
        name = _name;
        parentPath = _parentPath;
        cmakePath = _cmakePath;
        compilerPath = _compilerPath;
    }

    QString path;
    QString name;
    QString parentPath;
    QString cmakePath;
    QString compilerPath;
};


#endif // PROJECTCONFIG_H
