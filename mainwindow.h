#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "projectconfig.h"
#include "projectstorage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_okButton_clicked();

private:
    void generateDefaultDirectory(QString path, QString projectName);
    void startProgressImitation();
    QString outputText;
    ProjectConfig *projectConfig;
    ProjectStorage *projectStorage;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
