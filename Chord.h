/* 
 * File:   Chord.h
 * Author: astral
 *
 * Created on 21 Август 2012 г., 23:35
 */

#ifndef CHORD_H
#define	CHORD_H

#include "Note.h"
#include "SingleNote.h"
//#include "Bar.h"
#include <vector>

#define MAX_SUBNOTES 6

typedef struct SubnoteS {
    double tone;
    unsigned string; // Forced binding with string: turns off positioning towards 0-th fret algorithm in GameMode (if possible). 0 = disabled, >=0 = fret num is set on given string
    int octave_notes_pos; // defined during addition; used internally only (no getter for curr note)
} Subnote;

class Chord : public Note {
public:
    Chord(std::vector<double>& ntones, NoteLength nlength = nl1, unsigned nextension = 0);
    Chord(SingleNote& sn);
    virtual ~Chord();
    
    void AddTone (double t);
    void AddTone (Subnote s);
    void AddTone (); // Used on adding default (random) subnote: tries to add next 2nd white highest or, if not possible, next 2nd white lowest (2-nd white - to ensure that it's visible)
    QVector<double> GetChordTones (); // tones only
    QVector<Subnote *> GetChord (); // with string data
    int SubnoteCount() { return subnotes.size(); }
    // curr_subnote editing
    void SetCurrSubtone(QPointF p); // by mouseclick coords; sent by Tutor
    void ReleaseCurrSubtone() {curr_subnote = NULL;} // removes focus
    Subnote* CurrSubtone() {return curr_subnote;}
    void ModifyCurrSubnote (double t);
    void ModifyCurrSubnote (unsigned s);
    void ModifyCurrSubnote (Subnote s);
    void RaiseCurrSubnote ();
    void LowerCurrSubnote ();
    void RemoveCurrSubnote (); // the only way to remove notes from chord!
    
    // Graphics stuff
    void AdjustChord(QPointF point, int clef); // Adjust by highest note
    void SetStringForCurrSubnote (unsigned nstring) { curr_subnote->string = nstring; }
    unsigned GetStringOfCurrSubnote ()              { return curr_subnote->string; }
    void SetActive(bool state) {} // TODO morph for use of mouse pos and curr_subnote (re-)definition
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
signals: // special set to inform Bar about subtone insufficiency
    void ToSingleNote(Note*); // subtone count == 1; transform to SingleNote
    //void ToDestroy(Note *);    // subtone count == 0; delete from Bar vector
    
private:
    QVector<Subnote *> subnotes; // ToThinkAbout: use 'map' container?
    Subnote *curr_subnote;
};

#endif	/* CHORD_H */

