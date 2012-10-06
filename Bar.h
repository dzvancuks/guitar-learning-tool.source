/* 
 * File:   Bar.h
 * Author: astral
 *
 * Created on 21 Август 2012 г., 23:43
 */

#ifndef BAR_H
#define	BAR_H

#include <QtGui/QtGui>

//#include <vector>
#include <deque>
#include "SingleNote.h"
#include "Chord.h"

#define VISUAL_BAR_SPACING (VISUAL_NOTE_SPACING) // Spacing before or after border

#define NORMAL_COLOR Qt::darkGray
#define INCOMPLETE_COLOR Qt::green
#define EXCESS_COLOR Qt::red
#define DATA_COLOR Qt::black
#define GRAY_BORDER_COLOR Qt::lightGray

typedef enum ClefTypeE {
    treble = 1,
    bass = 2
} ClefType;

class Bar : public QGraphicsItem {
public:
    Bar(unsigned length, const char* chord);
    Bar(unsigned length);
    Bar(const Bar& orig);
    virtual ~Bar();
    
    const QString& GetBarChord() { return bar_chord; }
    unsigned GetId() { return id; }
    
    void SetRepeatStart(bool value = true) { repeat_start = value; } // call (false) on clear
    void SetRepeatEnd(int count = 2)       { repeat_end = count; }   // call (0) on clear; 2 - minimal repeat count; 1 - same as 0
    void ClearRepeatStart() { SetRepeatStart(false); }
    void ClearRepeatEnd()   { SetRepeatEnd(0); }
    bool IsRepeatStart()  { return repeat_start; }
    int  RepeatEndCount() const { return repeat_end; }
    void SetNextRepeatEndingId(unsigned id) { 
        assert(repeat_end == 2);
        next_repeat_ending = id; 
    }
    unsigned GetNextRepeatEndingId() { return next_repeat_ending; }
    
    void AddNoteBack(Note* note);
    void AddNoteAt  (Note* note, unsigned pos = 0);
    void RemoveNoteAt(unsigned pos);
    
    bool CanBeGrouped  (unsigned pos, unsigned n); // Check if n notes from pos can be grouped: t/f
    bool CanBeUngrouped(unsigned pos, unsigned n); // Check if n notes from pos can be ungrouped: t/f
    
    unsigned NoteCount() const { return notes.size(); }
    unsigned CheckBarLength(); // returns actual Note vector length.
    
    //0+ - actual Note vector length < length; 0 - equals; 0- - overlaps
    int CheckAvalableSpace() { return (int)length - (int)CheckBarLength();}
    
    bool IsLast() const; // TODO find a way to bypass const; needed by boundingRect
    qreal CalculateVisualBarLength() const;
    
    void DecreaseId(); // called on neibour Bar destruction; informs others forward
    
    void SetNextBar(Bar* bar) { next = bar; }
    void SetPreviousBar(Bar* bar) { previous = bar; }
    Bar* GetNextBar() { return next; }
    //Bar* GetPrevBar() { return previous; } // TODO dispose all "previous" pointers??
    void StichPointers(Bar* previous, Bar* next);
    void ClearNeighbour(); // clear neighbour pointers and stich them toghether

    void SetClef(ClefType clef) { this->clef = clef; }
    
    // Graphics sfuff
    qreal count_bar_length() const; 
    std::vector<QGraphicsItem*> GetVisualParts();
    
    QPointF GetFirstNotePos() { return first_note_global_pos; }
    QPointF GetPastLastNotePos() { return last_note_end_global_pos; }
    bool GrayAreaIntersection (QPointF pos) { // Point must be mapped to scene, i.e. item->scenePos()
        return pos.x() < first_note_global_pos.x() || pos.x() > last_note_end_global_pos.x();
    }
    QPointF NextBarFirstNotePos () {
        if (next)
            return next->GetFirstNotePos();
        else
            return QPointF(0, 0);
    }
    
    //void ArrangeNoteVisuals(QPointF start_point);
    QRectF boundingRect() const {
        qreal width = count_bar_length();
        return QRectF(0, -(VISUAL_NOTE_VSPACING*4), width, 3*(VISUAL_NOTE_VSPACING*4));
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    unsigned id; // copied from current_id state
    unsigned length; // bar length: X times of 64-th. I.e. "& 4/4" is 64, "& 5/8" is 40
    
    /* Repeat mechanics:
     *          rs                 re=4
     * 1         2         3         4
     * |--------|:---------|--------:|---------|
     * |--------|:---------|--------:|---------|
     * |--------|:---------|--------:|---------|
     * Repeat will take 4 times from bar 2 start to bar 3 end
     * 
     *          rs            ______re=2_______
     * 1         2         3 |1.     4|2.
     * |--------|:---------|--------:|---------|
     * |--------|:---------|--------:|---------|
     * |--------|:---------|--------:|---------|
     * Repeat will take 2 times from bar 2 start to bar 3 end in 1-st iteration,
     * and finish with bar 4, instead of 3, on 2-nd iteration (next_repeat_ending reference).
     * 
     * NB bar #1 should always be marked with rs (even if no re, just in case)
     */
    bool     repeat_start;
    unsigned repeat_end; // 0 or 1 indicates no repeat; 2 and above - repeat count
    unsigned next_repeat_ending; // id
    QString  bar_chord; // visuals above bar, i.e. "Am"
    
    QVector<Note*> notes; // Note/chord vector itself
    
    Bar *next, *previous; // uses to inform id change and minor info exchange.
    
    // Graphics sfuff
    QColor color; // Green - yet incomplete bar, black - filled bar, red - overflowned
    ClefType clef;
    
    QPointF first_note_global_pos;       // Positions (mapped to scene) of gray area
    QPointF last_note_end_global_pos;
    
    void DrawTailsSingle(QPainter *painter, Note* note);
    void DrawTailsStitched(QPainter *painter, QVector<QPointF>& points, NoteLength active_tail_type);
};

#endif	/* BAR_H */

