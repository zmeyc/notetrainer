// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QScopedPointer>
#include "MidiReader.h"
#include "ThirdParty/rtmidi/RtMidi.h"
#include "Utils/Utils.h"

MidiReader::MidiReader(QObject *parent)
    : QObject(parent)
{

}

MidiReader *MidiReader::sharedInstance()
{
    static MidiReader *instance = new MidiReader;
    return instance;
}

bool MidiReader::init()
{
    midiIn_.clear();

    try {
      midiIn_.reset(new RtMidiIn());
    } catch (RtMidiError &error) {
      lastErrorMessage_ = QString::fromUtf8(error.getMessage().c_str());
      return false;
    }

    uint portCount = midiIn_->getPortCount();
    qdbg << "MIDI input sources available: " << portCount << endl;
    QString portName;
    for (uint i = 0; i < portCount; ++i) {
      try {
        portName = QString::fromUtf8(midiIn_->getPortName(i).c_str());
      } catch (RtMidiError &error) {
        lastErrorMessage_ = QString::fromUtf8(error.getMessage().c_str());
        return false;
      }
      qdbg << "Input Port #" << i + 1 << ": " << portName << endl;
    }
    return true;
}

bool MidiReader::openPort(uint port)
try {
    uint portCount = midiIn_->getPortCount();
    if (port >= portCount) {
        lastErrorMessage_ = "port ";
        lastErrorMessage_ += QString::number(port);
        lastErrorMessage_ += " does not exist";
        return false;
    }

    midiIn_->openPort(port);
    midiIn_->setCallback(&onMidiMessageCB, this);
    midiIn_->ignoreTypes(false, false, false);

    return true;
} catch (RtMidiError &error) {
    lastErrorMessage_ = QString::fromUtf8(error.getMessage().c_str());
    return false;
}

QString MidiReader::lastErrorMessage() const
{
    return lastErrorMessage_;
}

void MidiReader::setLastErrorMessage(const QString &lastErrorMessage)
{
    lastErrorMessage_ = lastErrorMessage;
}

void MidiReader::onMidiMessage(double deltaTime,
                               std::vector<unsigned char> *message)
{
    size_t bytesCount = message->size();

    if (bytesCount == 1 && message->at(0) == 254)
        return; // Skip 'Active sense' bytes

    for (size_t i = 0; i < bytesCount; ++i)
        qdbg << "Byte " << i << " = " << (int)message->at(i) << ", ";
    if (bytesCount > 0)
        qdbg << "stamp = " << deltaTime << endl;

    if (bytesCount >= 3) {
        quint8 byte1 = (*message)[0];
        int channel = byte1 & 0b1111;
        int cmd = byte1 >> 4;
        qdbg << "[Channel " << channel << "] ";
        if (cmd == 0b1000) {
            // Note Off
            int key = (*message)[1];
            int velocity = (*message)[2];
            qdbg << "Note off: key=" << key << ", velocity=" << velocity;
            emit noteOff(key, velocity);
        } else if (cmd == 0b1001) {
            // Note On
            int key = (*message)[1];
            int velocity = (*message)[2];
            qdbg << "Note on: key=" << key << ", velocity=" << velocity;
            emit noteOn(key, velocity);
        }
        qdbg << endl;
    }

}

void MidiReader::onMidiMessageCB(double deltaTime,
                     std::vector<unsigned char> *message,
                     void *userData)
{
    MidiReader *reader = (MidiReader *)userData;
    reader->onMidiMessage(deltaTime, message);
}
