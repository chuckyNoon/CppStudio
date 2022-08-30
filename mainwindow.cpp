#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "projectbuilder.h"
#include "threadhelper.h"
#include <QtConcurrent/QtConcurrent>
#include <QLabel>
#include <filesystem>
#include <QScrollBar>
#include <sstream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString defaultFolder = "C:\\Users\\jju\\Documents"; // remove hardcode
    QString projectName = "q2z";

    projectConfig = new ProjectConfig(
        projectName,
        defaultFolder,
        "C:\\Qt\\Tools\\CMake_64\\bin\\cmake.exe",
        "C:\\Qt\\Tools\\mingw1120_64\\bin\\g++.exe"
        );
    projectStorage = new ProjectStorage(projectConfig);
    projectStorage->setupFiles();

    ui->codeTextEdit->setText(projectStorage->getMainCpp());

    ui->progressBar->setRange(0, 3);
    ui->progressBar->setVisible(false);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete projectStorage;
    delete projectConfig;
}


void MainWindow::on_okButton_clicked()
{
    if (projectConfig == nullptr){
        return;
    }
    projectStorage->updateMainCpp(ui->codeTextEdit->toPlainText());

    auto f = QtConcurrent::run(
        ProjectBuilder::buildAndRun,
        *projectConfig,
        [this](QString log) -> void {
            this->outputText +=  "\n" + log;
            ThreadHelper::dispatchToMainThread([this] {
                auto label = new QLabel(this->outputText);
                ui->outputScrollArea->setWidget(label);
                ui->outputScrollArea->verticalScrollBar()->setValue(ui->outputScrollArea->verticalScrollBar()->maximum());
                ui->progressBar->setValue(ui->progressBar->value() + 1);
                if (ui->progressBar->value() == 3) {// fix hardcode
                    ThreadHelper::dispatchDelayed(3, ([this] {ui->progressBar->setVisible(false);} ));
                }});
        });
    ui->progressBar->setValue(0);
    ui->progressBar->setVisible(true);
}
