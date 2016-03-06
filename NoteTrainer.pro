#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T17:28:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NoteTrainer
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    Utils/WidgetUtils.cpp \
    Controls/NoteSelector.cpp \
    Data/Note.cpp \
    Controls/NoteGuess.cpp

HEADERS  += MainWindow.h \
    Utils/WidgetUtils.h \
    Controls/NoteSelector.h \
    Data/Note.h \
    Controls/NoteGuess.h
