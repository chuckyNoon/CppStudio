QT       += core gui
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coloredtext.cpp \
    coloredtexthelper.cpp \
    filehelper.cpp \
    highlighter.cpp \
    main.cpp \
    mainwindow.cpp \
    prefirstwindow.cpp \
    projectbuilder.cpp \
    projectstorage.cpp

HEADERS += \
    coloredtext.h \
    coloredtexthelper.h \
    filehelper.h \
    highlighter.h \
    mainwindow.h \
    prefirstwindow.h \
    projectbuilder.h \
    projectconfig.h \
    projectstorage.h \
    threadhelper.h

FORMS += \
    mainwindow.ui \
    prefirstwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES +=
