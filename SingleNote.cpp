/* 
 * File:   SingleNote.cpp
 * Author: astral
 * 
 * Created on 21 Август 2012 г., 23:20
 */

#include "SingleNote.h"
#include <math.h>

SingleNote::SingleNote(NoteLength nlength, unsigned nextension, double npitch)
        : Note(nlength, nextension)
{
    pitch = npitch; // pitch = 0 => rest (type/length is defined by nlength)
    string = 0;
}

SingleNote::~SingleNote() {
}

void SingleNote::AdjustNote(QPointF point, int clef) { // TODO make BAR do the tails
    qreal n;
    int   in, inc;

#define F 698.456
#define A 220.0
    
    n = (log10( pitch / (clef == 1 ? F : A ) )) / 0.02508583297199843293447824122704; // determinate half-note distance: +0 - UP-, -0 DOWNWARDS
    in = floor (n + 0.5);
    inc = 0;
    if (in >= 0) {
        for(int i = 0; i < in; i++) {                                  // skip every b and # half-tone for pos starting from f/a
            int is = i % 12;
            if ((clef == 1 && (is == 0 || is == 2 || is == 4 || is == 7 || is == 9)) || // treble: start from F
                (clef == 2 && (is == 0 || is == 3 || is == 5 || is == 8 || is == 10)))  // bass  : start from A
                continue; // ignore bases to its #
            inc ++;
        }
    } else {
        for(int i = 0; i > in; i--) {                                  // skip every half-tone for pos starting from f/a
            int is = i % 12;
            if ((clef == 1 && (is == -2 || is == -4 || is == -7 || is == -9 || is == -11)) ||
                (clef == 2 && (is == -1 || is == -3 || is == -6 || is == -8 || is == -11)))
                continue; // ignore # to its bases
            inc --;
        }
    }
    inc = -inc;                                                        // reverse to Y vector direction
    setY(y() + inc * VISUAL_NOTE_VSPACING * 0.5);
}

QRectF SingleNote::boundingRect() const { 
    QRectF rect;
    if (pitch == 0) { // rest
        rect = QRectF(0, -VISUAL_SIZE, VISUAL_SIZE*2, VISUAL_SIZE*4); // Aligned on topmost line
    } else {
        rect = QRectF(0, -VISUAL_SIZE*0.5 + 1, VISUAL_SIZE, VISUAL_SIZE*0.75);
    }
    return rect; 
}

void SingleNote::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    if (active) {
        painter->setBrush(QColor(0,0,0,0)); // transparent
        painter->setPen(QPen(Qt::darkMagenta, 2));
        painter->drawRect(boundingRect().x()-VISUAL_SIZE/2, boundingRect().y()-VISUAL_SIZE/2, boundingRect().width()+VISUAL_SIZE, boundingRect().height()+VISUAL_SIZE);
    }

    // Rests
    if (pitch == 0) {
        // Actual drawing moved to Bar. Bounding rect handles triggering
        return;
    }
    
    QColor fill_color = (length >= nl2 ? QColor(0,0,0,0) : QColor(NOTE_COLOR));
    QColor outline_color = QColor(Qt::black);
    painter->setBrush(fill_color);
    painter->setPen(QPen(outline_color, 2));

    // Note Basics
    painter->drawEllipse(boundingRect());
    
    // Extension (dots) // TODO test
    painter->setBrush(outline_color); // solid
    painter->setPen(outline_color);
    for (unsigned i = 0; i < extension; i++) { 
        painter->drawEllipse(boundingRect().x() + boundingRect().width() + VISUAL_SIZE*(i+1)/1.5, 0,
                             VISUAL_NOTE_VSPACING*0.5, VISUAL_NOTE_VSPACING*0.5);
    }
    
    // b and #; for now, use # only
    int octave, oct_shift;
    double e = 0.1; // error rate
    for (octave = 0; octave < OCTAVES && octave_notes[(octave+1) * NOTES_PER_OCTAVE - 1] < pitch; octave++); // search pitch's octave
    for (oct_shift = 0; oct_shift < NOTES_PER_OCTAVE; oct_shift++) {                                         // search for note etalon itself
        double diff = octave_notes[octave * NOTES_PER_OCTAVE + oct_shift] - pitch;
        if (diff < 0) diff = -diff;
        if (diff < e) break;
    }
    switch (oct_shift){
        case 1:
        case 3:
        case 6: 
        case 8: 
        case 10: painter->drawText(boundingRect().x() - VISUAL_SIZE, 0, "#");
        default: break;
    }

}