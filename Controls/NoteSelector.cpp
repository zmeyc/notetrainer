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
        checkBox->setProperty("note", i);
        layout->addWidget(checkBox);
    }
    layout->addStretch(1);

    setLayout(layout);
}
