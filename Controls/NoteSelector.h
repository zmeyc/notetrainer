// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef NOTESELECTOR_H
#define NOTESELECTOR_H

#include <QWidget>
#include <QSet>
#include <QMap>
#include "Data/Note.h"

class QCheckBox;

class NoteSelector : public QWidget
{
    Q_OBJECT
public:
    explicit NoteSelector(QWidget *parent = 0);

    QSet<Note> notes() const;

signals:

public slots:

protected:
    QMap<int, QCheckBox *> checkBoxes_;
};

#endif // NOTESELECTOR_H
