#-------------------------------------------------
#
# Project created by QtCreator 2017-07-21T20:23:41
#
#-------------------------------------------------

QT       += core gui opengl
CONFIG += c++14

LIBS += -lOpengl32 -lglu32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = umesyu
TEMPLATE = app

INCLUDEPATH += ./include

SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/mainview.cpp \
    src/model.cpp

HEADERS  += include/mainwindow.hpp \
    include/mainview.hpp \
    include/model.hpp \
    include/vector.hpp \
    include/utility.hpp \
    include/view_status.hpp

FORMS    += ui/mainwindow.ui
