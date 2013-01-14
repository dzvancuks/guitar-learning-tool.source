/* 
 * File:   Carriage.h
 * Author: astral
 *
 * Created on 19 Сентябрь 2012 г., 22:41
 */

#ifndef CARRIAGE_H
#define	CARRIAGE_H

#include <QtGui/QtGui>

// For debugging TODO dispose
#include <QTime>
#include <QtDebug>

#include "Note.h"
#include "SingleNote.h"
#include "Chord.h"
#include "Bar.h"

#define CARRIAGE_COLOR Qt::blue
#define TICS 50

class Carriage : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Carriage(QObject* parent=0, unsigned bpm = 60);
    Carriage(const Carriage& orig);
    virtual ~Carriage();
    
    void SetState (bool state);
    void SetBPM (unsigned bpm) { this->bpm = bpm; back_from_pause = true; }

    void SetEtalon(NoteLength etalon) { 
        this->etalon = etalon; 
        RecalculateConstants();
    }
    
    // Graphics sfuff  
    QRectF boundingRect() const { return QRectF(0, -3*VISUAL_NOTE_VSPACING, 1, 11*VISUAL_NOTE_VSPACING); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
signals:
    void Finished ();
    void PassNote(Note*); // To Scholar
    void NewBar();
public slots:
    void ClearTimer();
protected:
     void advance(int step);
private:
    unsigned bpm;
    qreal visual_speed;
    bool play_state; // true - playing, false - paused
    bool back_from_pause; // to notify NOT to trigger timer and wait for next note
    QTimer timer;    // timer to ignore note passing
    QTime time;      // for timer adjustment
    
    Note *active_note;
    NoteLength etalon;
    QStack<Bar*> repeat_start;   // stack of repeat beginnings; (!!!) TODO on manual carriage movement, must be filled with all bars (with repeats) before carrage.
    QStack<Bar*> repeat_border;  // current repeat associative with repeat_start top; needs STACK, as track may contain repeats like this: |...|...:2|...:2|
    QStack<unsigned> repeat_count;   // clear stack on passing [repeat_border:repeat_count]==2; this stack correlates with repeat_border
    QStack<Bar*> repeat_border_ignore; // List of repeated bar_ends to prevent infinite loop on repeats like this: |...|...:2|...:2|; refilled from beginning (!) on new member
    Bar* repeat_start_ignore; // Used on clearing repeat_start top to prevent looping
    Bar* next_bar_repeat_1;   // Used on different repeat endings: if defined, use next from it on passing from it's previous bar
    
    qreal CA; // Adjustment constant
    qreal C1, C2; // global constants
    qreal v_est;
    void RecalculateConstants(); // on etalon change, like lesson load, or edit
};

#endif	/* CARRIAGE_H */

