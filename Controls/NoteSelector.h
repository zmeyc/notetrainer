// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef NOTESELECTOR_H
#define NOTESELECTOR_H

#include <QWidget>
#include <QSet>
#include <QMap>
#include "Data/Note.h"

class QGridLayout;
class QCheckBox;
class QSpinBox;
class QLabel;

class NoteSelector : public QWidget
{
    Q_OBJECT
public:
    explicit NoteSelector(QWidget *parent = 0);

    QSet<Note> notes() const;

signals:

public slots:

protected slots:
    void onOctaveFromChanged(int octave);
    void onOctaveToChanged(int octave);

protected:
    using OctaveCheckBoxes = QMap<int, QCheckBox *>;

    void updateOctaves();
    void updateCheckboxes();

    QGridLayout *checkBoxesLayout_ = nullptr;
    QSpinBox *octaveFromCheckBox_ = nullptr;
    QSpinBox *octaveToCheckBox_ = nullptr;
    QLabel *octavesLabel_ = nullptr;
    QMap<int, OctaveCheckBoxes> checkBoxes_;
    int octaveFrom_ = 0;
    int octaveTo_ = 0;
    int octaveCount_ = 0;
};

#endif // NOTESELECTOR_H
