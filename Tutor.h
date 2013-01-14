/* 
 * File:   Tutor.h
 * Author: astral
 *
 * Created on 10 Октябрь 2012 г., 20:22
 */

#ifndef _TUTOR_H
#define	_TUTOR_H

#include "ui_Tutor.h"
#include <cmath>
#include "QString"

#include "Lesson.h"
#include "Track.h"
#include "Bar.h"
#include "Note.h"

#include "Scholar.h"
#include "AudioIO.h"
#include "LoadStore.h"

#define DEFAULT_BPM 80
#define DEFAULT_BEAT_COUNT 1
#define DEFAULT_BEAT_LEN 1
#define DEFAULT_CLEF treble

#include "common.h"

class Tutor : public QMainWindow {
    Q_OBJECT
public:
    Tutor(AudioIO *audio);
    virtual ~Tutor();
  
public slots:
    void New();
    void Open();
    void Save();
    void SaveAs();
    void ShowAbout() { QMessageBox::about(this, QString("Guitar Learning Tool - About"), QString(AboutText)); }

    void ResizeSceneWidth(qreal nw) {
        scene->setSceneRect(0, 0, nw, scene->sceneRect().height());
    }
    void SceneUpdate() {
        scene->update(0, 0, widget.TutorMainView->geometry().width() + VISUAL_NOTE_SPACING*2, widget.TutorMainView->geometry().height());
    }
    
    // Editor's panel button signal handlers
    // Track
    void BPMChanged(int); // TODO: if <20 or >240, make 20 or 240 acc-ly
    void BCChanged(int);
    void BLChanged(int); // TODO on every step jump to nearest exponential value: 16->17 >> 32, 16->15 >> 8
    void ClefChanged(int);
    // Bar
    void AddBar();
    void DelBar();
    void ShiftRightBar();
    void ShiftLeftBar();
    void RepeatStart(int);
    void RepeatEnd(int); // TODO on 0 and 2->1 make always 0, on 0->1 make 2; as for repeat 1 === 0
    void RepeatOnNext(int); // TODO check if previous bar has not this flag and curr bar has RepeatEnd = 2
    void BarChord();
    // Note
    void AddNote();
    void DelNote();
    void ShiftRightNote();
    void ShiftLeftNote();
    void NoteLength(int);
    void NoteExtension(int); // TODO max 2
    void NoteContinue(int); // TODO, additional check for 2 active (selected) notes must be performed; must be LAST note in bar# and FIRST note in bar#+1
    void NoteSlide(int); // TODO, additional check for 2 active (selected) notes must be performed
    void NoteVibrato(int);
    void NoteGrouping(int);
    void NoteUngrouping(int);
    void NoteHOPO(int); // TODO make 3 slots??
    // Tone
    void AddTone();
    void AddToneSN_Chord(); // used after note substitution
    void DelTone();
    void ToneUp();
    void ToneDown();
    void ToneString(int);
    void ToneRest(int);
    
    // Mouse pointing/selecting routine
    void BarSelected(Bar*);
    void NoteSelected(Note*); // scan Ctrl key pressed for adding second note
    // TODO same for Scholar and Carriage positioning
    
    // few inline functions to change enable/disabled state for widgets. NB Change implementation in widget change
    void ChangeBarWidgetFrame(bool state);
    void ChangeBarWidgetFrameAllButAddBtn(bool state);
    void ChangeNoteWidgetFrame(bool state);
    void ChangeNoteWidgetFrameAllButAddBtn(bool state);
    void ChangeToneWidgetFrame(bool state);
    // Track is only changed by Frame state, no need in large functions like these
    
    // Play buttons
    void TrackPlay(); // TODO Create Mixer class and pass sound to it
    void BarPlay();
    void NotePlay();
    
    // Passing to/from Scholar
    void StartScholar();
    void FetchFromScholar(Lesson*);
    
    // Note (SN <-> Chord) substitution
    void SubstituteNote(Note*, Note*);
signals:
    void PassToScholar(Lesson*); // TODO create emit by view->switch to Scholar and vice-versa

    // Keyboard and Mouse point&click handler
protected:
    void closeEvent(QCloseEvent *event);
    bool eventFilter( QObject * o , QEvent * e );
    
private:
    Ui::Tutor widget;
    //Scholar *scholar;
    QGraphicsScene *scene;//CustomScene *scene; // QGraphicsScene *scene;
    AudioIO *audio; // Used for Note changes palyback
    
    Lesson *lesson;
    Track  *track;
    Bar    *active_bar; // The one that selected
    Note   *active_note1; // The one that selected
    Note   *active_note2; // This one is to mace continuations/slide pairs with note1
    
    QString file_name;
};

#endif	/* _TUTOR_H */
