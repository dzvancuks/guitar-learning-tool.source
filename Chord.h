/* 
 * File:   Chord.h
 * Author: astral
 *
 * Created on 21 Август 2012 г., 23:35
 */

#ifndef CHORD_H
#define	CHORD_H

#include "Note.h"
#include <vector>

class Chord : public Note {
public:
    Chord(NoteLength nlength, unsigned nextension, std::vector<double>& ntones);
    Chord(const Chord& orig);
    virtual ~Chord();
    
    //virtual unsigned GetToneCount() { return tones.size(); }
    
    // Graphics sfuff
    void AdjustChordByY(qreal first_line_y){} // TODO
    QRectF boundingRect() const { 
        return QRectF(0,0,0,0);              // TODO
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {} // TODO
private:
    std::vector<double> tones; // ToThinkAbout: use 'map' container?
    //unsigned          tones_count; // use tones.size
};

#endif	/* CHORD_H */

