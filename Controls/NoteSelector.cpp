// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#include <QVBoxLayout>
#include <QCheckBox>
#include <QSpinBox>
#include <QLabel>
#include <QVariant>
#include "NoteSelector.h"
#include "Data/Note.h"

NoteSelector::NoteSelector(QWidget *parent) : QWidget(parent)
{
    octaveFromCheckBox_ = new QSpinBox;
    octaveFromCheckBox_->setValue(3);
    octaveFromCheckBox_->setMinimum(-1);
    octaveFromCheckBox_->setMaximum(8);
    connect(octaveFromCheckBox_, SIGNAL(valueChanged(int)),
            this, SLOT(onOctaveFromChanged(int)));

    octaveToCheckBox_ = new QSpinBox;
    octaveToCheckBox_->setValue(5);
    octaveToCheckBox_->setMinimum(-1);
    octaveToCheckBox_->setMaximum(8);
    connect(octaveToCheckBox_, SIGNAL(valueChanged(int)),
            this, SLOT(onOctaveToChanged(int)));

    QHBoxLayout *octaveSelectionLayout = new QHBoxLayout;
    octaveSelectionLayout->setContentsMargins(0, 0, 0, 0);
    octaveSelectionLayout->addWidget(octaveFromCheckBox_);
    octaveSelectionLayout->addWidget(octaveToCheckBox_);
    octaveSelectionLayout->addStretch(1);

    octavesLabel_ = new QLabel;

    checkBoxesLayout_ = new QGridLayout;
    checkBoxesLayout_->setContentsMargins(0, 0, 0, 0);

    updateOctaves();

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    layout->addStretch(1);
    layout->addLayout(octaveSelectionLayout);
    layout->addWidget(octavesLabel_);
    layout->addLayout(checkBoxesLayout_);

    layout->addStretch(1);

    setLayout(layout);
}

QSet<Note> NoteSelector::notes() const
{
    QSet<Note> result;
    for (int octave = octaveFrom_; octave <= octaveTo_; ++octave) {
        const OctaveCheckBoxes &ocb = checkBoxes_[octave];
        for (int pitch = 0; pitch < (int) Note::Pitch::Count; ++pitch) {
            if (ocb[pitch]->isChecked())
                result.insert(Note((Note::Pitch)pitch, octave));
        }
    }
    return result;
}

void NoteSelector::updateOctaves()
{
    octaveFrom_ = octaveFromCheckBox_->value();
    octaveTo_ = octaveToCheckBox_->value();
    if (octaveFrom_ > octaveTo_)
        octaveFrom_ = octaveTo_;
    octaveCount_ = octaveTo_ - octaveFrom_ + 1;
    octavesLabel_->setText(tr("Octave range: [%1, %2], %3 octave%4.")
                           .arg(octaveFrom_)
                           .arg(octaveTo_)
                           .arg(octaveCount_)
                           .arg(octaveCount_ == 1 ? "" : "s"));
    updateCheckboxes();
}

void NoteSelector::updateCheckboxes()
{
    QLayoutItem *item;
    while ((item = checkBoxesLayout_->takeAt(0)) != 0) {
        delete item->widget();
        delete item;
    }
    checkBoxes_.clear();

    checkBoxesLayout_->setSpacing(5);
    for (int octave = octaveFrom_; octave <= octaveTo_; ++octave) {
        OctaveCheckBoxes &ocb = checkBoxes_[octave];
        for (int pitch = 0; pitch < (int) Note::Pitch::Count; ++pitch) {
            QCheckBox *checkBox = new QCheckBox(Note::pitchName((Note::Pitch)pitch));
            //checkBox->setChecked(true);
            checkBox->setProperty("octave", octave);
            checkBox->setProperty("pitch", pitch);
            int column = octave - octaveFrom_;
            checkBoxesLayout_->addWidget(checkBox, pitch, column);
            checkBoxesLayout_->setColumnStretch(column, 0);

            ocb[pitch] = checkBox;
        }
    }
    checkBoxesLayout_->setColumnStretch(octaveTo_ + 1, 1);
}

int NoteSelector::octaveTo() const
{
    return octaveTo_;
}

int NoteSelector::octaveFrom() const
{
    return octaveFrom_;
}

void NoteSelector::onOctaveFromChanged(int octave)
{
    Q_UNUSED(octave);
    updateOctaves();
}

void NoteSelector::onOctaveToChanged(int octave)
{
    Q_UNUSED(octave);
    updateOctaves();
}
