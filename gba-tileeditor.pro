# set options
CONFIG += qt debug c++17

# set the QT modules we need
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

# build an application
TARGET = gba-tileeditor
TEMPLATE = app

# specify all the files we need
SOURCES += \
          src/editorwindow.cc \
          src/main.cc \
          src/map.cc \
          src/mapview.cc \
          src/newdialog.cc \
          src/paletteview.cc

HEADERS += \
          src/command.hh \
          src/editorwindow.hh \
          src/map.hh \
          src/mapview.hh \
          src/newdialog.hh \
          src/paletteview.hh \
          src/saveheadercommand.hh \
          src/savejsoncommand.hh \
          src/json.hpp \
          src/savesourcescommand.hh

INCLUDEPATH += src

FORMS += forms/mainwindow.ui \
         forms/newmap.ui
RESOURCES = icons.qrc

