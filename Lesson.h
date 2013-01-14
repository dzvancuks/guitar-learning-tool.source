/* 
 * File:   Lesson.h
 * Author: astral
 *
 * Created on 22 Август 2012 г., 21:52
 */

#ifndef LESSON_H
#define	LESSON_H

#include "Track.h"
#include "Note.h"

/* For test only; TODO dispose */
#include "Bar.h"
#include "SingleNote.h"
#include "Chord.h"

class Lesson {
public:
    Lesson();
    virtual ~Lesson();
    
    
    
    void LoadLesson(QFile f); // TODO
    
    void SetTrack(Track *t) { track = t; }
    void DeleteTrack() { if (track) track->ClearBars(); delete track; }
    Track* GetTrack() { return track; }
    
    void SetBPM (unsigned bpm) { this->bpm = bpm; }
    unsigned GetBPM () { return bpm; }
    
    std::vector<QGraphicsItem*> GetVisualParts();
    qreal GetVisualLength() { return (track ? track->GetVisualLength() : 0); }
    // TODO sync Carriage w/ 1-st bar's 1-st note
    QPointF GetStartingPos() { return (track ? track->GetStartingPos() : QPointF(0, 0)); }
    unsigned GetBeatCount () { return (track ? track->GetBeatCount() : 0); }
    unsigned GetBeatLength() { return (track ? track->GetBeatLength() : 0); }
private:
    Track *track;
    unsigned bpm;
    
    // TODO
    // Soundtrack soundtrack; // background sound; sync. with track
    // AVHelper helper;       // Audio-visual helper, i.e. video of hand position
    // int      avhelper_sync; // lesson and AVH sync: <0 - video first, then lesson, >0 - video shows during lesson track, =0 - sync. start
};

#endif	/* LESSON_H */

