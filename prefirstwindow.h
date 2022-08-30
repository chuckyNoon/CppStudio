#ifndef PREFIRSTWINDOW_H
#define PREFIRSTWINDOW_H

#include <QDialog>
#include <QFileDialog>
#include "projectconfig.h"

namespace Ui {
class PreFirstWindow;
}

class PreFirstWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PreFirstWindow(QWidget *parent = nullptr);
    ~PreFirstWindow();

private slots:
    void on_directoryButton_clicked();

    void on_okPushBut_clicked();

    void on_cmakeButton_clicked();

    void on_compilerButton_clicked();

private:
    Ui::PreFirstWindow *ui;
signals:
    void signal(ProjectConfig*);
};

#endif // PREFIRSTWINDOW_H
