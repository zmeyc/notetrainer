// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef MIDIREADER_H
#define MIDIREADER_H

#include <vector>
#include <QObject>
#include <QString>
#include <QSharedPointer>

class RtMidiIn;

class MidiReader: public QObject
{
    Q_OBJECT
public:
    MidiReader(QObject *parent = nullptr);

    static MidiReader *sharedInstance();

    bool init();
    bool openPort(uint port);

    QString lastErrorMessage() const;
    void setLastErrorMessage(const QString &lastErrorMessage);

signals:
    void noteOn(int key, int velocity);
    void noteOff(int key, int velocity);

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
