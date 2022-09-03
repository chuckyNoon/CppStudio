#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "projectconfig.h"
#include "projectstorage.h"
#include <QFileDialog>
#include <QTextEdit>
#include "highlighter.h"
#include "prefirstwindow.h"

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

    void slot(ProjectConfig*);

    void newProject();
    void newFile();
    void open();
    void save();
    void closeFile();
    void exit();
    void undo();
    void redo();
    void showLeftSidebar();
    void showRightSideBar();
    void build();
    void run();
    void clean();
    void sendFeedback();
    void about();

private:
    void generateDefaultDirectory(QString path, QString projectName);
    void startProgressImitation();
    void setupEditor();


    void createMenus();
    void createActions();

    Highlighter *highlighter;

    QString outputText;
    ProjectConfig *projectConfig;
    ProjectStorage *projectStorage;
    Ui::MainWindow *ui;
    PreFirstWindow *firstwindow;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *buildMenu;
    QMenu *helpMenu;

    //file
    QAction *newProjectAction;
    QAction *newFileAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *closeFileAction;
    QAction *exitAction;

    //edit
    QAction *undoAction;
    QAction *redoAction;

    //view
    QAction *showLeftSidebarAction;
    QAction *showRightSidebarAction;

    //buid
    QAction *buildAction;
    QAction *runAction;
    QAction *cleanAction;

    //help
    QAction *sendFeedbackAction;
    QAction *aboutAction;
};

#endif // MAINWINDOW_H
