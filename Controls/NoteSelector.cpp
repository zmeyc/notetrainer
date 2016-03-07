// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QVBoxLayout>
#include <QCheckBox>
#include <QVariant>
#include "NoteSelector.h"
#include "Data/Note.h"

NoteSelector::NoteSelector(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addStretch(1);
    for (int i = 0; i < (int) Note::Count; ++i) {
        QCheckBox *checkBox = new QCheckBox(noteName((Note)i));
        checkBox->setChecked(true);
        checkBox->setProperty("note", i);
        layout->addWidget(checkBox);

        checkBoxes_[i] = checkBox;
    }
    layout->addStretch(1);

    setLayout(layout);
}

QSet<Note> NoteSelector::notes() const
{
    QSet<Note> result;
    for (int i = 0; i < (int) Note::Count; ++i) {
        if (checkBoxes_[i]->isChecked())
            result.insert((Note)i);
    }
    return result;
}
