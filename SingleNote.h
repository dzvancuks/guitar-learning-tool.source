/* 
 * File:   SingleNote.h
 * Author: astral
 *
 * Created on 21 Август 2012 г., 23:20
 */

#ifndef SINGLENOTE_H
#define	SINGLENOTE_H

#include "Note.h"

class SingleNote : public Note {
public:
    SingleNote(NoteLength nlength = nl1, unsigned nextension = 0, double npitch = 0);
    virtual ~SingleNote();
    
    void   SetPitch (double np) { pitch = np; } // pitch = 0 => pauze (type/length is defined by nlength)
    double GetPitch ()          { return pitch; }
    
    // Graphics stuff
    void AdjustNote(QPointF point, int clef);
    void SetString (unsigned nstring) { string = nstring; }
    unsigned GetString ()             { return string; }
    
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    double pitch;
    unsigned string; // Forced binding with string: turns off positioning towards 0-th fret algorithm in GameMode (if possible). 0 = disabled, >=0 = fret num is set on given string
};

#endif	/* SINGLENOTE_H */

