// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include "StaffSettings.h"

StaffSettings::StaffSettings(QWidget *parent) : QWidget(parent)
{
    QLabel *queueLengthLabel = new QLabel(tr("Preview Queue Length"));

    queueLengthSpinBox_ = new QSpinBox;
    queueLengthSpinBox_->setValue(6);
    queueLengthSpinBox_->setMinimum(1);
    queueLengthSpinBox_->setMaximum(12);
    connect(queueLengthSpinBox_, SIGNAL(valueChanged(int)),
            this, SLOT(onQueueLengthChanged(int)));

    showNoteNamesCheckBox_ = new QCheckBox(tr("Show Note Names"));
    showNoteNamesCheckBox_->setChecked(true);
    connect(showNoteNamesCheckBox_, SIGNAL(clicked(bool)),
            this, SLOT(onShowNoteNamesClicked(bool)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(queueLengthLabel);
    layout->addWidget(queueLengthSpinBox_, 0, Qt::AlignLeft);
    layout->addWidget(showNoteNamesCheckBox_, 0, Qt::AlignLeft);
    setLayout(layout);

    onQueueLengthChanged(queueLengthSpinBox_->value());
    onShowNoteNamesClicked(showNoteNamesCheckBox_->isChecked());
}

int StaffSettings::queueLength() const
{
    return queueLength_;
}

bool StaffSettings::showNoteNames() const
{
    return showNoteNames_;
}

void StaffSettings::onQueueLengthChanged(int value)
{
    queueLength_ = value;
}

void StaffSettings::onShowNoteNamesClicked(bool checked)
{
    showNoteNames_ = checked;
}
