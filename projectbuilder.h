#ifndef PROJECTBUILDER_H
#define PROJECTBUILDER_H

#include <QString>
#include <functional>
#include "projectconfig.h"

class ProjectBuilder
{
public:
    ProjectBuilder();
    static void build(ProjectConfig config);
    static void clean(ProjectConfig config);
    static void buildAndRun(ProjectConfig config, std::function<void(QString)> callback);
private:
    static QString runProcess(QString command);
};

#endif // PROJECTBUILDER_H
