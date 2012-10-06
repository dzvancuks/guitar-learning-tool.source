/* 
 * File:   Chord.cpp
 * Author: astral
 * 
 * Created on 21 Август 2012 г., 23:35
 */

#include <vector>

#include "Chord.h"

Chord::Chord(NoteLength nlength, unsigned nextension, std::vector<double>& ntones
            ) : Note(nlength, nextension)
{
    unsigned i;
    
    //assert(ntones.size() != 0);
    for(i = 0; i < ntones.size(); i++){
        tones.push_back(ntones[i]);
    }
}

Chord::Chord(const Chord& orig) {
    //TODO
}

Chord::~Chord() {
}

