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
    continuation = false;
    continued = false;
    slide = false;
    slided = false;
    vibrato = false;
    HO = false;
    PO = false;
    grouping = 0;
    ungrouping = 0;
    
    //tail_direction = false;
}

Note::Note(const Note& orig) {
    length = orig.length;
    continuation = orig.continuation;
    continued = orig.continued;
    slide = orig.slide;
    slided = orig.slided;
    vibrato = orig.vibrato;
    HO = orig.HO;
    PO = orig.PO;
    grouping = orig.grouping;
    ungrouping = orig.ungrouping;
}

Note::~Note() {
}


