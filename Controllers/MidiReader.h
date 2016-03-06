// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef MIDIREADER_H
#define MIDIREADER_H

#include <vector>
#include <QString>
#include <QSharedPointer>

class RtMidiIn;

class MidiReader
{
public:
    MidiReader();

    static MidiReader *sharedInstance();

    bool init();
    bool openPort(uint port);

    QString lastErrorMessage() const;
    void setLastErrorMessage(const QString &lastErrorMessage);

protected:
    void onMidiMessage(double deltaTime,
                       std::vector<unsigned char> *message);
    static void onMidiMessageCB(double deltaTime,
                             std::vector<unsigned char> *message,
                             void *userData);

    QSharedPointer<RtMidiIn> midiIn_;
    QString lastErrorMessage_;
};

#endif // MIDIREADER_H
