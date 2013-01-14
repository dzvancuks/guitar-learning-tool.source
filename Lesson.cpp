/* 
 * File:   Lesson.cpp
 * Author: astral
 * 
 * Created on 22 Август 2012 г., 21:52
 */

#include "Lesson.h"

// TEST only
#define BC 3
#define BL 4

Lesson::Lesson() {
    track = NULL;
    bpm = 0;

    /*
    // TEST
    Bar *tmpbar1, *tmpbar2, *tmpbar3, *tmpbar4, *tmpbar5;
    
    track = new Track(treble, BC, BL);
    SetBPM(80);

    tmpbar1 = new Bar(CalculateBarLength(BC, BL));
    //tmpbar1->SetRepeatEnd(2);
    tmpbar2 = new Bar(CalculateBarLength(BC, BL));
    //tmpbar2->SetRepeatEnd(2);
    //tmpbar2->SetNextRepeatEndingId(3);
    tmpbar3 = new Bar(CalculateBarLength(BC, BL), "Am"); // empty bar
    tmpbar3->SetRepeatStart(true);
    tmpbar4 = new Bar(CalculateBarLength(BC, BL)); // empty bar
    tmpbar4->SetRepeatEnd(2);
    tmpbar4->SetNextRepeatEndingId(5);
    tmpbar5 = new Bar(CalculateBarLength(BC, BL)); // empty bar
    tmpbar5->SetRepeatEnd(2);
    
    track->AddBarBack(tmpbar2);  // just to mix things up :)
    track->AddBarAt(tmpbar1, 0);
    track->AddBarBack(tmpbar3);
    track->AddBarBack(tmpbar4);
    track->AddBarBack(tmpbar5);
    
    tmpbar1->AddNoteBack(new SingleNote(nl2, 0, 261.626)); // C
    tmpbar1->AddNoteBack(new SingleNote(nl4, 0, 293.665)); // D
    
    tmpbar2->AddNoteBack(new SingleNote(nl8, 0, 329.628)); // E
    tmpbar2->AddNoteBack(new SingleNote(nl8, 0, 349.228)); // F
    tmpbar2->AddNoteBack(new SingleNote(nl8, 0, 391.995)); // G
    tmpbar2->AddNoteBack(new SingleNote(nl8, 0, 440.000)); // A
    tmpbar2->AddNoteBack(new SingleNote(nl4, 0, 493.883)); // B
    
    tmpbar3->AddNoteBack(new SingleNote(nl16, 0, 220.000)); // Am
    tmpbar3->AddNoteBack(new SingleNote(nl16, 0, 261.626));
    tmpbar3->AddNoteBack(new SingleNote(nl16, 0, 329.628));
    tmpbar3->AddNoteBack(new SingleNote(nl16, 0, 261.626));
    tmpbar3->AddNoteBack(new SingleNote(nl16, 0, 220.000));
    tmpbar3->AddNoteBack(new SingleNote(nl16, 0, 0));       // Rest
    tmpbar3->AddNoteBack(new SingleNote(nl8, 0, 0));
    tmpbar3->AddNoteBack(new SingleNote(nl4, 0, 0));
    
    tmpbar4->AddNoteBack(new SingleNote(nl8, 0, 466.164)); // A#
    tmpbar4->AddNoteBack(new SingleNote(nl2, 0, 415.305)); // G#
    tmpbar4->AddNoteBack(new SingleNote(nl8, 0, 369.994)); // F#
    
    tmpbar5->AddNoteBack(new SingleNote(nl4, 1, 311.127)); // D#
    tmpbar5->AddNoteBack(new SingleNote(nl4, 1, 277.183)); // C#
    */
}

Lesson::~Lesson() {
}

std::vector<QGraphicsItem*> Lesson::GetVisualParts() {
    std::vector<QGraphicsItem*> ret;
    
    if (track) {
        ret.push_back(track);
        std::vector<QGraphicsItem*> visuals = track->GetVisualParts();
        ret.insert(ret.end(), visuals.begin(), visuals.end());
    }
    
    return ret;
}

void Lesson::LoadLesson(QFile f) {
    // TODO
    return;
}