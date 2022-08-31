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
    setWindowTitle(tr("Syntax Highlighter"));
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

