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
    
    unsigned CalculateBarLength(unsigned beat_c = 1, unsigned beat_l = 4) {
        return beat_c * (nl1 / beat_l);
    }
    
    void LoadLesson(QFile f);
    
    //Track* GetTrack() { return track; }
    std::vector<QGraphicsItem*> GetVisualParts();
    qreal GetVisualLength() { return track->GetVisualLength(); }
    // TODO sync Carriage w/ 1-st bar's 1-st note
    QPointF GetStartingPos() { return track->GetStartingPos(); }
    unsigned GetBeatCount () { return track->GetBeatCount(); }
    unsigned GetBeatLength() { return track->GetBeatLength(); }
private:
    Track *track;
    unsigned bpm;
    
    // TODO
    // Soundtrack soundtrack; // background sound; sync. with track
    // AVHelper helper;       // Audio-visual helper, i.e. video of hand position
    // int      avhelper_sync; // lesson and AVH sync: <0 - video first, then lesson, >0 - video shows during lesson track, =0 - sync. start
};

#endif	/* LESSON_H */

