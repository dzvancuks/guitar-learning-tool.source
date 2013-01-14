/* 
 * File:   Chord.cpp
 * Author: astral
 * 
 * Created on 21 Август 2012 г., 23:35
 */

#include <vector>

#include "Chord.h"
#include "Bar.h"

Chord::Chord(std::vector<double>& ntones, NoteLength nlength, unsigned nextension 
            ) : Note(nlength, nextension)
{
    unsigned i;
    
    for(i = 0; i < ntones.size(); i++) {
        int tone_global_pos; // position in octave_notes
        Subnote *tmp = (Subnote *)malloc(sizeof(Subnote));
        tmp->tone = ntones[i];
        tmp->string = 0;
        tone_global_pos = FreqToOctavePos(tmp->tone);
        if (tone_global_pos > -1) {
            tmp->octave_notes_pos = tone_global_pos;
        } else {
            continue; // don't add tone that does not exists
        }
        
        subnotes.push_back(tmp);
    }
    //assert(subnotes.size() > 0); // at least one existing tone must be added
    
    curr_subnote = NULL;
}

Chord::Chord(SingleNote& sn) : Note(sn.GetBasicLength(), sn.GetExtensionCount())
{
    int tone_global_pos; // position in octave_notes
    Subnote *tmp = (Subnote *)malloc(sizeof(Subnote));
    tmp->tone = sn.GetPitch();
    tmp->string = sn.GetString();
    tone_global_pos = FreqToOctavePos(tmp->tone);
    if (tone_global_pos > -1) {
        tmp->octave_notes_pos = tone_global_pos;
        subnotes.push_back(tmp);
    }
    assert(subnotes.size() > 0); // octave_notes_pos must be found
    
    setPos(sn.pos());
    
    curr_subnote = NULL;
    
    // TODO Copy other members from sn
}

Chord::~Chord() {
    curr_subnote = NULL;
    foreach(Subnote *s, subnotes) {
        free(s);
    }
}

// Aligned on topmost line
QRectF Chord::boundingRect() const { // TODO from topmost to bottommost tones
    QRectF rect;
    int   in, inc, shift;
    double lowest_tone = octave_notes[TOTAL_TONES-1], highest_tone = 0, n;
    Subnote *s_high, *s_low;
    
    //if (subnotes.size() == 0) return; Chord should be deleted
    assert(subnotes.size() > 0);
    
    foreach(Subnote *s, subnotes) {
        if (highest_tone < s->tone) {
            highest_tone = s->tone;
            s_high = s;
        }
        if (lowest_tone > s->tone) {
            lowest_tone = s->tone;
            s_low = s;
        }
    }
    
    shift = s_high->octave_notes_pos%12;
     
    n = (log10( highest_tone / lowest_tone )) / 0.02508583297199843293447824122704; // determinate half-note distance: +0 - UP-, -0 DOWNWARDS
    in = floor (n + 0.5);
    inc = 0;
    if (shift == 1 || shift == 3 || shift == 6 || shift == 8 || shift == 10) { // # pos is same to base
        shift -= 1;
        in -= 1;
    }
    while(in--) {                                  // skip every b and # half-tone for pos
        if (shift == 0) { shift = 11; }
        else { shift -= 1; }
        //if (shift == 1 || shift == 3 || shift == 6 || shift == 8 || shift == 10) { // ignore all # positions
        if (shift == 0 || shift == 2 || shift == 5 || shift == 7 || shift == 9) { // ignore all # positions
            continue; // ignore bases to its #
        }
        inc++;
    }
    
    if (inc == 0)
        rect = QRectF(0, -VISUAL_SIZE*0.5 + 1, VISUAL_SIZE, VISUAL_SIZE*0.75);
    else
        rect = QRectF(0, -VISUAL_SIZE*0.5 + 1, VISUAL_SIZE, (VISUAL_SIZE*0.5)*inc + VISUAL_SIZE*0.75); // h: each white note is allocated on every 1/2 of line size + note itself spacing
    return rect; 
}

void Chord::AddTone (double t) {
    if (GetChord().size() >= MAX_SUBNOTES) return;
    
    int tone_global_pos; // position in octave_notes
    tone_global_pos = FreqToOctavePos(t);
    assert(tone_global_pos > -1); // TODO try-catch; note MUST be found, or we're dealing with corrupted/malformed data
    
    Subnote *sn = (Subnote *)malloc(sizeof(Subnote));
    sn->tone = t;
    sn->string = 0;
    sn->octave_notes_pos = tone_global_pos;
    subnotes.push_back(sn);
    
    // TEST
    //curr_subnote = sn;
}
void Chord::AddTone (Subnote s) {
    if (GetChord().size() >= MAX_SUBNOTES) return;
    
    int tone_global_pos; // position in octave_notes
    tone_global_pos = FreqToOctavePos(s.tone);
    assert(tone_global_pos > -1); // TODO try-catch; note MUST be found, or we're dealing with corrupted/malformed data
    
    Subnote *sn = (Subnote *)malloc(sizeof(Subnote));
    sn->tone = s.tone;
    sn->string = s.string;
    sn->octave_notes_pos = tone_global_pos;
    subnotes.push_back(sn);
}
void Chord::AddTone () { // Used on adding default (random) subnote: tries to add next highest or, if not possible, next lowest
    if (GetChord().size() >= MAX_SUBNOTES) return;
    
    int tone_global_pos; // position in octave_notes
    double tone = 0;
    Subnote *s_to_find;

    // at first try to add new tone at top ...
    foreach(Subnote *s, subnotes) {
        if (tone < s->tone) {
            tone = s->tone;
            s_to_find = s;
        }
    }
    if (s_to_find->octave_notes_pos < TOTAL_TONES - 1) {
        tone_global_pos = s_to_find->octave_notes_pos + 1;
        switch (tone_global_pos % 12) { // a bit higher - 2nd white
            case 1:
            case 3:
            case 6:
            case 8:
            case 10:
                tone_global_pos += (tone_global_pos+1 < TOTAL_TONES - 1 ? 1 : 0);
        }
    } else {
        // ... otherwise, try to add to very bottom ...
        tone = octave_notes[TOTAL_TONES-1];
        foreach(Subnote *s, subnotes) {
            if (tone > s->tone) {
                tone = s->tone;
                s_to_find = s;
            }
        }
        if (s_to_find->octave_notes_pos > 0) {
            tone_global_pos = s_to_find->octave_notes_pos - 1;
        } else {
            // ... note to tutor: "You are just fooling around. Nobody gonna play it"
        }
    }

    Subnote *sn = (Subnote *)malloc(sizeof(Subnote));
    sn->tone = octave_notes[tone_global_pos];
    sn->string = 0;
    sn->octave_notes_pos = tone_global_pos;
    subnotes.push_back(sn);
}
QVector<double> Chord::GetChordTones () { // tones only
    QVector<double> ret;
    
    foreach(Subnote *s, subnotes) {
        ret.push_back(s->tone);
    }
    
    return ret;
}
QVector<Subnote *> Chord::GetChord () { // with string data
    return subnotes;
}

void Chord::SetCurrSubtone(QPointF p) {
    QQueue<Subnote *> sorted;
    foreach(Subnote *s, subnotes) { // sort descending
        if (sorted.isEmpty()) sorted.push_back(s);
        else {
            bool inserted = false;
            for(int i = 0; i < sorted.size(); i++) {
                if (s->octave_notes_pos > sorted[i]->octave_notes_pos) { // sorting by global positions
                    sorted.insert(i, s);
                    inserted = true;
                    break;
                }
            }
            if (!inserted) {sorted.push_back(s);}
        }
    }
    
    int visual_line_diff_total = 0;
    for(int i = 0; i < sorted.size(); i++) {
        qreal y;
        int visual_line_diff = 0;
        
        if (i != 0) { // ignore top note visual shifting, as it is constant to boundingRect.y
            for (int j = sorted[i-1]->octave_notes_pos; j >= sorted[i]->octave_notes_pos; j--) {
                int m = j%12;
                if (m == 0 || m == 2 || m == 5 || m == 7 || m == 9) { // ignore all # to base positions
                    continue; // ignore bases to its #
                }
                visual_line_diff++;
            }
        }
        visual_line_diff_total += visual_line_diff;
        y = VISUAL_SIZE*0.5*visual_line_diff_total;
        
        if (y > p.y()) {
            curr_subnote = sorted[i];
            return;
        }
    }
}
void Chord::ModifyCurrSubnote (double t) {
    if (curr_subnote) {
        curr_subnote->tone = t; // overlap check with other tones should be made externally
        curr_subnote->octave_notes_pos = FreqToOctavePos(curr_subnote->tone);
        assert(curr_subnote->octave_notes_pos > -1);
    }
    
    // update();
}
void Chord::ModifyCurrSubnote (unsigned s) { // string only
    if (curr_subnote) {
        curr_subnote->string = s;
    }
}
void Chord::ModifyCurrSubnote (Subnote s) {
    if (curr_subnote) {
        int tone_global_pos;
        curr_subnote->tone = s.tone; // overlap check with other tones should be made externally
        curr_subnote->string = s.string;
        tone_global_pos = FreqToOctavePos(curr_subnote->tone);
        assert(tone_global_pos > -1); // TODO try-catch; note MUST be found, or we're dealing with corrupted/malformed data
        curr_subnote->octave_notes_pos = tone_global_pos;
    }
}
void Chord::RaiseCurrSubnote () {
    if (!curr_subnote) return;
    
    int new_pos = curr_subnote->octave_notes_pos;
    while(++new_pos < TOTAL_TONES) {
        bool acceptable_pos = true;
        foreach(Subnote *s, subnotes) {
            if (octave_notes[new_pos] != s->tone) continue; // search for first acceptable
            else acceptable_pos = false;
        }
        if (acceptable_pos) break; // no overlap found
    }
    if (new_pos < TOTAL_TONES) { // possible that tone will be out-of range; TODO limit to 2K Hz for guitars
        ModifyCurrSubnote(octave_notes[new_pos]);
    }
}
void Chord::LowerCurrSubnote () {
    if (!curr_subnote) return;
    
    int new_pos = curr_subnote->octave_notes_pos;
    while(--new_pos >= 0) {
        bool acceptable_pos = true;
        foreach(Subnote *s, subnotes) {
            if (octave_notes[new_pos] != s->tone) continue; // search for first acceptable
            else acceptable_pos = false;
        }
        if (acceptable_pos) break; // no overlap found
    }
    if (new_pos >= 0) { // possible that tone will be out-of range; TODO limit to 60 Hz for guitars
        ModifyCurrSubnote(octave_notes[new_pos]);
    }
}
void Chord::RemoveCurrSubnote () {
    if (curr_subnote) {
        int pos = subnotes.indexOf(curr_subnote);
        assert(pos >= 0); // TODO try-catch
        subnotes.remove(pos);
    }
    free(curr_subnote);
    curr_subnote = NULL;
    
    //Bar *parent = (Bar*)GetParentBar();
    //assert(parent);
    //AdjustChord(pos(), parent->GetClef());
    
    //if (subnotes.size() == 1) {emit ToSingleNote(this);} // Tell Bar that this chord must be transformed into SingleNote
    //if (subnotes.size() == 0) emit ToDestroy(this); // DON'T DO Tell Bar that this chord must be force deleted
}

void Chord::AdjustChord(QPointF point, int clef) {
    qreal n;
    int   in, inc;
    double highest_tone = 0;
    
    //if (subnotes.size() == 0) return; Chord should be deleted
    assert(subnotes.size() > 0);
    
    foreach(Subnote *s, subnotes) {
        if (highest_tone < s->tone) highest_tone = s->tone;
    }

#define F 698.456
#define A 220.0
    
    // TODO simplify just as in paint(), by using octave_notes_pos
    n = (log10( highest_tone / (clef == 1 ? F : A ) )) / 0.02508583297199843293447824122704; // determinate half-note distance: +0 - UP-, -0 DOWNWARDS
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
void Chord::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    //if (subnotes.size() == 0) return; Chord should be deleted
    assert(subnotes.size() > 0);
    
    if (curr_subnote) {
        qreal curr_y;
        double highest_tone = 0;
        int shift, in, inc;
        Subnote *s_high;
        
        painter->setBrush(QColor(0,0,0,0)); // transparent
        painter->setPen(QPen(Qt::darkMagenta, 2));
        
        foreach(Subnote *s, subnotes) {
            if (highest_tone < s->tone) {
                highest_tone = s->tone;
                s_high = s;
            }
        }

        shift = s_high->octave_notes_pos%12;

        in = s_high->octave_notes_pos;//floor (n + 0.5);
        inc = 0;
        while(in-- > curr_subnote->octave_notes_pos) {       // skip every b and # half-tone for pos
            if (shift == 0) { shift = 11; }
            else { shift -= 1; }
            if (shift == 0 || shift == 2 || shift == 5 || shift == 7 || shift == 9) { // ignore all base of '#' position shifting
                continue; // ignore bases to its #
            }
            inc++;
        }
        curr_y = boundingRect().y() + VISUAL_SIZE*0.5*(inc+1);
        
        painter->drawRect(boundingRect().x() - VISUAL_SIZE/2, curr_y - VISUAL_SIZE/2 - 1, boundingRect().width() + VISUAL_SIZE, VISUAL_SIZE);
    }
    
    // draw from bottom for '#' reason
    QQueue<Subnote *> drawable;
    foreach(Subnote *s, subnotes) { // sort ascending
        if (drawable.isEmpty()) drawable.push_back(s);
        else {
            bool inserted = false;
            for(int i = 0; i < drawable.size(); i++) {
                if (s->octave_notes_pos < drawable[i]->octave_notes_pos) { // sorting by global positions
                    drawable.insert(i, s);
                    inserted = true;
                    break;
                }
            }
            if (!inserted) {drawable.push_back(s);}
        }
    }
    
    // special 2 points to draw tail base - line between notes; rest of the tail is handled by Bar
    if (this->GetBasicLength() < nl1) {
        painter->drawLine(
                boundingRect().x() + VISUAL_SIZE, boundingRect().y() + VISUAL_SIZE*0.5,
                boundingRect().x() + VISUAL_SIZE, boundingRect().y() + boundingRect().height() - VISUAL_SIZE*0.5);
    }
            
    int visual_line_diff_total = 0;
    for(int i = 0; i < drawable.size(); i++) {
        //qreal y;
        int visual_line_diff = 0;
        bool sharp = false; // whether put # sign or not
        
        if (i != 0) { // ignore bottom note visual shifting, as it is constant to boundingRect.y+h
            for (int j = drawable[i-1]->octave_notes_pos + 1; j <= drawable[i]->octave_notes_pos; j++) {
                int m = j%12;
                if (m == 1 || m == 3 || m == 6 || m == 8 || m == 10) { // ignore all # positions
                    sharp = true;
                    continue; // ignore bases to its #
                }
                sharp = false;
                visual_line_diff++;
            }
        } else { 
            switch (drawable[i]->octave_notes_pos % 12) {
                case 1:
                case 3:
                case 6: 
                case 8: 
                case 10:
                    sharp = true;
            }
        }
        visual_line_diff_total += visual_line_diff;

        // Note Basics
        QColor fill_color = (length >= nl2 ? QColor(0,0,0,0) : QColor(NOTE_COLOR));
        QColor outline_color = QColor(Qt::black);
        painter->setBrush(fill_color);
        painter->setPen(QPen(outline_color, 2));
        if (!visual_line_diff) {
            if (i == 0) {
                painter->drawEllipse(boundingRect().x(), boundingRect().y() + boundingRect().height() - VISUAL_SIZE*0.75, VISUAL_SIZE, VISUAL_SIZE*0.75);
            } else { // # @ same as base note
                // draw a little to the left with #, if base is present
                painter->drawEllipse(boundingRect().x() - VISUAL_SIZE*0.5,
                        boundingRect().y() + boundingRect().height() - VISUAL_SIZE*0.5*visual_line_diff_total - VISUAL_SIZE,//*0.75,// - /*and a bit higher*/ - VISUAL_SIZE*0.25,
                        VISUAL_SIZE, VISUAL_SIZE*0.75);
            }
        } else {
            painter->drawEllipse(boundingRect().x(), boundingRect().y() + boundingRect().height() - VISUAL_SIZE*0.5*visual_line_diff_total - VISUAL_SIZE*0.75, VISUAL_SIZE, VISUAL_SIZE*0.75);
        }
        

        // Extension (dots)
        painter->setBrush(outline_color); // solid
        painter->setPen(outline_color);
        for (unsigned n = 0; n < extension; n++) { 
            painter->drawEllipse(boundingRect().x() + boundingRect().width() + VISUAL_SIZE*(n+1)/1.5, 0,
                                VISUAL_NOTE_VSPACING*0.5, VISUAL_NOTE_VSPACING*0.5);
        }

        // b and #; for now, use # only
        //int oct_shift = drawable[i]->octave_notes_pos%12;
        if (sharp) {
            painter->drawText(boundingRect().x() - (visual_line_diff == 0 ? VISUAL_SIZE : VISUAL_SIZE*1.5),
                    boundingRect().y() + boundingRect().height() - VISUAL_SIZE*0.5*visual_line_diff_total,
                    "#");
        }
        /*
        switch (oct_shift){
            case 1:
            case 3:
            case 6: 
            case 8: 
            case 10: painter->drawText(boundingRect().x() - (visual_line_diff == 0 ? VISUAL_SIZE : VISUAL_SIZE*1.5), 0, "#"); // 1.5 is added due to shifting a bit to the left
            default: break;
        }
        */
    }
}