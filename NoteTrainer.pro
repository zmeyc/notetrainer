#-------------------------------------------------
#
# Project created by QtCreator 2016-03-06T17:28:48
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG   += c++11

TARGET = NoteTrainer
TEMPLATE = app

macx: {
    DEFINES += __MACOSX_CORE__
    LIBS += -framework CoreMIDI -framework CoreAudio -framework CoreFoundation
}

SOURCES += main.cpp\
        MainWindow.cpp \
    Utils/WidgetUtils.cpp \
    Controls/NoteSelector.cpp \
    Data/Note.cpp \
    Controls/NoteGuess.cpp \
    Controls/NoteView.cpp \
    Models/NoteViewScene.cpp \
    GraphicsItems/StaffGraphicsItem.cpp \
    Utils/Utils.cpp \
    GraphicsItems/NoteGraphicsItem.cpp \
    ThirdParty/rtmidi/RtMidi.cpp \
    Controllers/MidiReader.cpp \
    Controls/StaffSettings.cpp

HEADERS  += MainWindow.h \
    Utils/WidgetUtils.h \
    Controls/NoteSelector.h \
    Data/Note.h \
    Controls/NoteGuess.h \
    Controls/NoteView.h \
    Models/NoteViewScene.h \
    GraphicsItems/StaffGraphicsItem.h \
    Utils/Utils.h \
    GraphicsItems/NoteGraphicsItem.h \
    ThirdParty/rtmidi/RtMidi.h \
    Controllers/MidiReader.h \
    Controls/StaffSettings.h

RESOURCES += \
    NoteTrainer.qrc
