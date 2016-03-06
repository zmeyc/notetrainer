// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "NoteGuess.h"

NoteGuess::NoteGuess(QWidget *parent) : QWidget(parent)
{
    QLabel *correct = new QLabel("Correct");
    QLabel *wrong = new QLabel("Wrong");
    QPushButton *reset = new QPushButton("Reset");

    QHBoxLayout *panelLayout = new QHBoxLayout;
    panelLayout->addWidget(correct);
    panelLayout->addWidget(wrong);
    panelLayout->addStretch(1);
    panelLayout->addWidget(reset);

    QLabel *staff = new QLabel("Staff");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(staff);
    layout->addLayout(panelLayout);

    setLayout(layout);
}
