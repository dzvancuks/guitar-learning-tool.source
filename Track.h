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
    
    void AddBarBack(Bar* bar);
    void AddBarAt(Bar* bar, unsigned pos);
    void RemoveBarAt(unsigned pos);
    
    void SetBeatCount (unsigned bc) { beat_count  = bc; }
    void SetBeatLength(unsigned bl) { beat_length = bl; }
    unsigned GetBeatCount  () { return beat_count; }
    unsigned GetBeatLength () { return beat_length; }
    
    unsigned CalculateLength() { return beat_count * (nl1 / beat_length); }
    
    // Graphics sfuff  
    QPointF GetStartingPos() { return bars.front()->GetFirstNotePos(); } 
    qreal GetVisualLength();
    
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    std::vector<QGraphicsItem*> GetVisualParts();
private:
    ClefType clef; // 1 - treble; 2 - bass
    
    unsigned beat_count;  // as for 3 - total beats per bar
    unsigned beat_length; //        4 - each beat is 1/4
    
    std::vector<Bar*> bars; // Bar vector itself   //TODO Bar& -> Bar* ??
    
    // Graphics sfuff
    QPointF bpos; // bar's top-left point position - highest visible line
    qreal   spacing; // space between two lines // TODO Dispose ?? Using macro
    qreal   clef_w;
    //qreal   total_w; // total width for boundingRect()
};

#endif	/* TRACK_H */

