// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef STAFFSETTINGS_H
#define STAFFSETTINGS_H

#include <QWidget>

class QSpinBox;
class QCheckBox;

class StaffSettings : public QWidget
{
    Q_OBJECT
public:
    explicit StaffSettings(QWidget *parent = 0);

    int queueLength() const;
    bool showNoteNames() const;

signals:

public slots:

protected slots:
    void onQueueLengthChanged(int value);
    void onShowNoteNamesClicked(bool checked);

protected:
    QSpinBox *queueLengthSpinBox_ = nullptr;
    QCheckBox *showNoteNamesCheckBox_ = nullptr;
    int queueLength_ = 0;
    bool showNoteNames_ = false;
};

#endif // STAFFSETTINGS_H
