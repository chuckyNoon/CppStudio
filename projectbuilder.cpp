#include "projectbuilder.h"
#include "projectconfig.h"
#include <QApplication>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <QProcess>
#include <QDebug>
#include <QtConcurrent/QtConcurrent>
#include <QThread>
#include <filesystem>


ProjectBuilder::ProjectBuilder()// class must be refactored
{

}

void ProjectBuilder::build(ProjectConfig config)
{
    QString buildDirectory = config.parentPath + "\\build-" + config.name + "-Debug";

    QString generateCmakeFilesCommand = config.cmakePath + " -S "+ config.path + " -B " + buildDirectory + " \"-DCMAKE_CXX_COMPILER:FILEPATH=" + config.compilerPath + "\"";
    runProcess(generateCmakeFilesCommand);

    QString buildProgramCommand = "\"" + config.cmakePath + "\""  + " --build " + "\"" +buildDirectory + "\"";
    runProcess(buildProgramCommand);
}

void ProjectBuilder::clean(ProjectConfig config)
{
    QString buildDirectory = config.parentPath + "\\build-" + config.name + "-Debug";
    std::filesystem::remove_all(buildDirectory.toStdString());
}

void ProjectBuilder::buildAndRun(ProjectConfig config, std::function<void(QString)> callback)
{
    QString buildDirectory = config.parentPath + "\\build-" + config.name + "-Debug";

    QString generateCmakeFilesCommand = config.cmakePath + " -S "+ config.path + " -B " + buildDirectory + " \"-DCMAKE_CXX_COMPILER:FILEPATH=" + config.compilerPath + "\"";
    callback(runProcess(generateCmakeFilesCommand));

    QString buildProgramCommand = "\"" + config.cmakePath + "\""  + " --build " + "\"" +buildDirectory + "\"";
    callback(runProcess(buildProgramCommand));

    QString runProgramCommand = "\"" + buildDirectory + "\\Debug\\" + config.name + ".exe" + "\"";
    callback(runProcess(runProgramCommand));
}

QString ProjectBuilder::runProcess(QString command)
{
    QProcess process;
    // process.setProcessChannelMode(QProcess::ForwardedChannels);
    process.start(command);
    if (!process.waitForStarted())
        return "1";//
    else if (!process.waitForFinished())
        return "2";//
    return process.readAll();
}
