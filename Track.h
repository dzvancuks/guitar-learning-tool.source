/* 
 * File:   Track.h
 * Author: astral
 *
 * Created on 22 Август 2012 г., 21:40
 */

#ifndef TRACK_H
#define	TRACK_H

#include <QtGui/QtGui>

#include <stdio.h>
#include <iostream>

#include <vector>
#include "Bar.h"


/*
typedef enum ClefTypeE {
    treble = 1,
    bass = 2
} ClefType;
*/

class Track : public QGraphicsItem {
public:
    Track(ClefType clef = treble, unsigned beat_count = 1, unsigned beat_length = 1);
    Track(const Track& orig);
    virtual ~Track();
    
    void SetClef(ClefType clef);
    ClefType GetClef() { return clef; }
    
    void AddBarBack(Bar* bar);
    void AddBarAt(Bar* bar, unsigned pos);
    void RemoveBarAt(unsigned pos); // Not deleted!
    void ClearBars();
    void SwapBars(Bar* bar1, Bar* bar2);
    QVector<Bar*> GetBars() {return bars;}
    
    void SetBeatCount (unsigned bc) { beat_count  = bc; }
    void SetBeatLength(unsigned bl) { beat_length = bl; }
    unsigned GetBeatCount  () { return beat_count; }
    unsigned GetBeatLength () { return beat_length; }
    
    unsigned CalculateBarLength() { return beat_count * (nl1 / beat_length); }
    void RecalculateAllBarsLength() { 
        foreach(Bar* bar, bars) {
            bar->SetLength(CalculateBarLength());
            bar->update();
        } 
    }
    
    // Graphics stuff  
    QPointF GetStartingPos() { return (!bars.isEmpty() ? bars.front()->GetFirstNotePos() : QPointF(0, 0)); } 
    qreal GetVisualLength();
    
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    std::vector<QGraphicsItem*> GetVisualParts();
private:
    ClefType clef; // 1 - treble; 2 - bass
    
    unsigned beat_count;  // as for 3 - total beats per bar
    unsigned beat_length; //        4 - each beat is 1/4
    
    QVector<Bar*> bars; // Bar vector itself
    
    // Graphics sfuff
    QPointF bpos; // bar's top-left point position - highest visible line
    qreal   spacing; // space between two lines // TODO Dispose ?? Using macro
    qreal   clef_w;
    //qreal   total_w; // total width for boundingRect()
};

#endif	/* TRACK_H */

