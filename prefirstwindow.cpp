#include "prefirstwindow.h"
#include "ui_prefirstwindow.h"
#include "projectconfig.h"
#include "threadhelper.h"

PreFirstWindow::PreFirstWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreFirstWindow)
{
    ui->setupUi(this);
    on_okPushBut_clicked(); // delete

    ThreadHelper::dispatchDelayed(1, [this]{this->on_okPushBut_clicked();});
}

PreFirstWindow::~PreFirstWindow()
{
    delete ui;
}

void PreFirstWindow::on_directoryButton_clicked()
{
    QString _yDirectory = QFileDialog::getExistingDirectory(this, "Choose your directory", "C:\\");
    ui->directoryLineEdit->setText(_yDirectory);

}


void PreFirstWindow::on_okPushBut_clicked()
{
    auto newConfig = new ProjectConfig(ui->nameLineEdit->displayText(),
                      ui->directoryLineEdit->displayText(),
                      ui->cmakeLineEdit->displayText(),
                      ui->compilerLineEdit->displayText());
    auto newConfig1 = new ProjectConfig("polygon", "C:/Users/jju/Documents","C:/Qt/Tools/CMake_64/bin/cmake.exe", "C:/Qt/Tools/mingw1120_64/bin/g++.exe"); // delete
    emit signal(newConfig1);
    this->hide();
    this->close();
}


void PreFirstWindow::on_cmakeButton_clicked()
{
    QString _yDirectory = QFileDialog::getOpenFileName(this, "Choose your directory", "C:\\");
    ui->cmakeLineEdit->setText(_yDirectory);
}


void PreFirstWindow::on_compilerButton_clicked()
{
    QString _yDirectory = QFileDialog::getOpenFileName(this, "Choose your directory", "C:\\");
    ui->compilerLineEdit->setText(_yDirectory);
}

