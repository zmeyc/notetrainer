// NoteTrainer (c) 2016 Andrey Fidrya. MIT license. See LICENSE for more information.

#ifndef STAFFGRAPHICSITEM_H
#define STAFFGRAPHICSITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QMargins>
#include <QMap>
#include <QSet>
#include "Data/Note.h"

class NoteGraphicsItem;

class StaffGraphicsItem: public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit StaffGraphicsItem(QGraphicsItem *parent = nullptr);

    void setOctaveRange(int fromOctave, int toOctave);
    void addNote(int queueIndex, const Note &note, int group);
    bool hasNote(int queueIndex, const Note &note, int group);
    bool hasNote(int queueIndex, const Note &note);
    void queuePop();
    int queueLength();
    void queuePushNote(const Note &note, int group);
    void removeNote(int queueIndex, const Note &note, int group);
    void removeAllNotes();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = nullptr) override;
signals:

public slots:

protected:
    using Notes = QMap<Note, NoteGraphicsItem *>;
    using NoteGroups = QMap<int, Notes>;
    using Queue = QVector<NoteGroups>;

    int notesAreaWidth() const;
    void updateNotePositions();

    Queue noteGroupsQueue_;
    QMargins contentMargins_;
    int fromOctave_ = 0;
    int toOctave_ = 0;
};

#endif // STAFFGRAPHICSITEM_H
