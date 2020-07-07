# set options
CONFIG += qt debug c++17

# set the QT modules we need
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

# build an application
TARGET = gba-tileeditor
TEMPLATE = app

# specify all the files we need
SOURCES += src/main.cpp \
          src/editorwindow.cpp \
          src/newdialog.cpp \
          src/paletteview.cpp \
          src/mapview.cpp \
          src/map.cpp

HEADERS += src/editorwindow.h \
          src/command.h \
          src/newdialog.h \
          src/paletteview.h \
          src/mapview.h \
          src/map.h \
          src/saveheadercommand.h \
          src/savesourcescommand.h \
          src/savejsoncommand.h \
          src/json.hpp

INCLUDEPATH += src

FORMS += forms/mainwindow.ui \
         forms/newmap.ui
RESOURCES = icons.qrc

