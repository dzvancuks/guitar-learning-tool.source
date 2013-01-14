/* 
 * File:   Note.cpp
 * Author: astral
 * 
 * Created on 21 Август 2012 г., 22:35
 */

#include "Note.h"

VisualSizeSpeed GlobalGetVisualSizeSpeed(NoteLength length, unsigned extension) {
    VisualSizeSpeed result;
    NoteLength recursive;// = length;

    assert(length >= nl64);
    
    switch (length) {
        case nl64: result.size = 1.; result.speed = 8; recursive = nl64; break;
        case nl32: result.size = 1.; result.speed = 4; recursive = nl64; break;
        case nl16: result.size = 1.; result.speed = 2; recursive = nl32; break;
        case nl8: result.size = 1.; result.speed = 1; recursive = nl16; break;
        case nl4: result.size = 2.; result.speed = 1; recursive = nl8; break;
        case nl2: result.size = 4.; result.speed = 1; recursive = nl4; break;
        case nl1: result.size = 8.; result.speed = 1; recursive = nl2; break;
        default: result.size = 0.; result.speed = 0;            // Abnormal state;
    }
    if (extension) {
        result.size += GlobalGetVisualSizeSpeed(recursive, extension-1).size;
    }

    return result;
}

Note::Note(NoteLength nlength, unsigned nextension) {
    assert(nlength != 0);
    length = nlength;
    assert(nextension < 3); // I doubt if it needs more than that
    extension = nextension;
    //bar = NULL;
    continuation = NULL; // TODO dispose flags?
    continued = NULL;
    //continueTo = continuedFrom = NULL;
    slide = NULL;
    slided = NULL;
    //slideTo = slidedFrom = NULL;
    vibrato = false;
    HO = false;
    PO = false;
    grouping = 0;
    ungrouping = 0;
    
    //setFlag(QGraphicsItem::ItemIsSelectable, true);
    active = false;
}

Note::Note(const Note& orig) {
    length = orig.length;
    extension = orig.extension;
    //bar = orig.bar;
    continuation = orig.continuation;
    continued = orig.continued;
    //continueTo = orig.continueTo;
    //continuedFrom = orig.continuedFrom;
    slide = orig.slide;
    slided = orig.slided;
    //slideTo = orig.slideTo;
    //slidedFrom = orig.slidedFrom;
    vibrato = orig.vibrato;
    HO = orig.HO;
    PO = orig.PO;
    grouping = orig.grouping;
    ungrouping = orig.ungrouping;
    
    //setFlag(QGraphicsItem::ItemIsSelectable, true);
    active = false;
}

Note::~Note() {
}

int Note::FreqToOctavePos (double freq) {
    int tone_global_pos; // position in octave_notes
    double e = 0.1; // error rate
    for (tone_global_pos = 0; tone_global_pos <= TOTAL_TONES; tone_global_pos++) { // search tone shift
        double diff = octave_notes[tone_global_pos] - freq;
        if (diff < 0) diff = -diff;
        if (diff < e) break;
    }
    return (tone_global_pos < TOTAL_TONES ? tone_global_pos : -1);
}
