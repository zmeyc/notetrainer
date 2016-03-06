// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QVBoxLayout>
#include <QCheckBox>
#include "NoteSelector.h"
#include "Data/Note.h"

NoteSelector::NoteSelector(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;

    for (int i = 0; i < (int) Note::Count; ++i) {
        QCheckBox *checkBox = new QCheckBox(noteName((Note)i));
        layout->addWidget(checkBox);
    }

    setLayout(layout);
}
