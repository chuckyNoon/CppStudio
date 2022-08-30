#include "prefirstwindow.h"
#include "ui_prefirstwindow.h"
#include "projectconfig.h"

PreFirstWindow::PreFirstWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreFirstWindow)
{
    ui->setupUi(this);
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
    ui->nameLineEdit->displayText();
    auto newConfig = new ProjectConfig(ui->nameLineEdit->displayText(),
                      ui->directoryLineEdit->displayText(),
                      ui->cmakeLineEdit->displayText(),
                      ui->compilerLineEdit->displayText());
    emit signal(newConfig);
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

