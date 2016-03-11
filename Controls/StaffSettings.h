// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef STAFFSETTINGS_H
#define STAFFSETTINGS_H

#include <QWidget>

class QSpinBox;

class StaffSettings : public QWidget
{
    Q_OBJECT
public:
    explicit StaffSettings(QWidget *parent = 0);

    int queueLength() const;

signals:
    void queueLengthChanged(int queueLength);

public slots:

protected slots:
    void onQueueLengthChanged(int value);

protected:
    QSpinBox *queueLengthSpinBox_ = nullptr;
    int queueLength_;
};

#endif // STAFFSETTINGS_H
