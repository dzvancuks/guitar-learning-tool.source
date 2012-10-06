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
    SingleNote(const SingleNote& orig);
    virtual ~SingleNote();
    
    void   SetPitch (double np) { pitch = np; } // pitch = 0 => pauze (type/length is defined by nlength)
    double GetPitch ()          { return pitch; }
    
    //virtual unsigned GetToneCount() { return 1; }
    
    // Graphics sfuff
    void AdjustNote(QPointF point, int clef);
    QRectF boundingRect() const { return QRectF(0, -VISUAL_SIZE*0.5 + 1, VISUAL_SIZE, VISUAL_SIZE*0.75); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    double pitch;
};

#endif	/* SINGLENOTE_H */

