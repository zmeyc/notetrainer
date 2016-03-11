// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include "StaffSettings.h"

StaffSettings::StaffSettings(QWidget *parent) : QWidget(parent)
{
    QLabel *queueLengthLabel = new QLabel(tr("Preview Queue Length"));

    queueLengthSpinBox_ = new QSpinBox;
    queueLengthSpinBox_->setValue(4);
    queueLengthSpinBox_->setMinimum(1);
    queueLengthSpinBox_->setMaximum(12);
    connect(queueLengthSpinBox_, SIGNAL(valueChanged(int)),
            this, SLOT(onQueueLengthChanged(int)));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(queueLengthLabel);
    layout->addWidget(queueLengthSpinBox_, 0, Qt::AlignLeft);
    setLayout(layout);

    onQueueLengthChanged(queueLengthSpinBox_->value());
}

int StaffSettings::queueLength() const
{
    return queueLength_;
}

void StaffSettings::onQueueLengthChanged(int value)
{
    queueLength_ = value;
    emit queueLengthChanged(queueLength_);
}
