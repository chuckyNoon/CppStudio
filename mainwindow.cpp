#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "projectbuilder.h"
#include "threadhelper.h"
#include <QtConcurrent/QtConcurrent>
#include <QLabel>
#include <filesystem>
#include <QScrollBar>
#include <sstream>
#include <QListWidget>
#include <QMessageBox>
#include "uihelper.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QListWidgetItem *item_1 = new QListWidgetItem("1");
    ui->fileListView->addItem(item_1);
    QListWidgetItem *item_2 = new QListWidgetItem("2");
    ui->fileListView->addItem(item_2);
    QListWidgetItem *item_3 = new QListWidgetItem("3");
    ui->fileListView->addItem(item_3);
    QListWidgetItem *item_4 = new QListWidgetItem("4");
    ui->fileListView->addItem(item_4);
    QListWidgetItem *item_5 = new QListWidgetItem("5");
    ui->fileListView->addItem(item_5);
    QListWidgetItem *item_6 = new QListWidgetItem("6");
    ui->fileListView->addItem(item_6);

    firstwindow = new PreFirstWindow;
    firstwindow -> show();
    connect(firstwindow, &PreFirstWindow::signal, this, &MainWindow::slot);

    ui->progressBar->setRange(0, 3);
    ui->progressBar->setVisible(false);
    ui->progressBar->setValue(0);

    setWindowTitle(tr("Cpp Studio"));
    createActions();
    createMenus();
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



void MainWindow::slot(ProjectConfig* newConfig)
{
    projectConfig = newConfig;
    projectStorage = new ProjectStorage(projectConfig);
    projectStorage->setupFiles();

    setupEditor();
}

void MainWindow::newProject()
{
    UiHelper::showMessage("newProject"); // to implement logic
}

void MainWindow::newFile()
{
    UiHelper::showMessage("newFile"); // to implement logic
}

void MainWindow::open()
{
    UiHelper::showMessage("open"); // to implement logic
}

void MainWindow::save()
{
    UiHelper::showMessage("save"); // to implement logic
}

void MainWindow::closeFile()
{
    UiHelper::showMessage("closeFile"); // to implement logic
}

void MainWindow::exit()
{
    UiHelper::showMessage("exit"); // to implement logic
}

void MainWindow::undo()
{
    UiHelper::showMessage("undo"); // to implement logic
}

void MainWindow::redo()
{
    UiHelper::showMessage("redo"); // to implement logic
}

void MainWindow::showLeftSidebar()
{
    UiHelper::showMessage("showLeftSidebar"); // to implement logic
}

void MainWindow::showRightSideBar()
{
    UiHelper::showMessage("showRightSideBar"); // to implement logic
}

void MainWindow::build()
{
    UiHelper::showMessage("build"); // to implement logic
}

void MainWindow::run()
{
    UiHelper::showMessage("run"); // to implement logic
}

void MainWindow::clean()
{
    UiHelper::showMessage("clean"); // to implement logic
}

void MainWindow::sendFeedback()
{
    UiHelper::showMessage("sendFeedback"); // to implement logic
}

void MainWindow::about()
{
    UiHelper::showMessage("about"); // to implement logic
}


void MainWindow::setupEditor()
{
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);


    ui->codeTextEdit->setFont(font);

    highlighter = new Highlighter(ui->codeTextEdit->document());

    ui->codeTextEdit->setPlainText(projectStorage->getMainCpp());
    qDebug() << "here";
}

void MainWindow::createActions()
{
    newProjectAction = new QAction(tr("&New Porject"), this);
    connect(newProjectAction, &QAction::triggered, this, &MainWindow::newProject);

    newFileAction = new QAction(tr("&New file"), this);
    connect(newFileAction, &QAction::triggered, this, &MainWindow::newFile);

    openAction = new QAction(tr("&Open"), this);
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    saveAction = new QAction(tr("&Save"), this);
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    closeFileAction = new QAction(tr("&Close file"), this);
    connect(closeFileAction, &QAction::triggered, this, &MainWindow::closeFile);

    exitAction = new QAction(tr("&Exit project"), this);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exit);

    undoAction = new QAction(tr("&Undo"), this);
    connect(undoAction, &QAction::triggered, this, &MainWindow::undo);

    redoAction = new QAction(tr("&Redo"), this);
    connect(redoAction, &QAction::triggered, this, &MainWindow::redo);

    showLeftSidebarAction = new QAction(tr("&Show left sidebar"), this);
    connect(showLeftSidebarAction, &QAction::triggered, this, &MainWindow::showLeftSidebar);

    showRightSidebarAction = new QAction(tr("&Show right sidebar"), this);
    connect(showRightSidebarAction, &QAction::triggered, this, &MainWindow::showRightSideBar);

    buildAction = new QAction(tr("&Build"), this);
    connect(buildAction, &QAction::triggered, this, &MainWindow::build);

    runAction = new QAction(tr("&Run"), this);
    connect(runAction, &QAction::triggered, this, &MainWindow::run);

    cleanAction = new QAction(tr("&Clean"), this);
    connect(cleanAction, &QAction::triggered, this, &MainWindow::clean);

    sendFeedbackAction = new QAction(tr("&Send feedback"), this);
    connect(sendFeedbackAction, &QAction::triggered, this, &MainWindow::sendFeedback);

    aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newProjectAction);
    fileMenu->addAction(newFileAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(closeFileAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(undoAction);
    editMenu->addAction(redoAction);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(showLeftSidebarAction);
    viewMenu->addAction(showRightSidebarAction);

    buildMenu = menuBar()->addMenu(tr("&Build"));
    buildMenu->addAction(buildAction);
    buildMenu->addAction(cleanAction);
    buildMenu->addAction(runAction);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(sendFeedbackAction);
    helpMenu->addAction(aboutAction);
}
