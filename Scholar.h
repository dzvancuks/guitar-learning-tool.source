/* 
 * File:   Scholar.h
 * Author: astral
 *
 * Created on 20 Июль 2012 г., 17:50
 */

#ifndef _SCHOLAR_H
#define	_SCHOLAR_H

#include <QtGui/QtGui>
#include <QtCore/QtCore>
#include <vector>
#include <QTimer>

#include "ui_Scholar.h"
#include "Lesson.h"
#include "Note.h"
#include "Carriage.h"

#include "Tutor.h"
#include "AudioIO.h"
#include "Mixer.h"
#include "Metronome.h"
//#include "Effects.h"
#include "SingleToneAnalyzer.h"
#include "ChordAnalyzer.h"
#include "Tuner.h"

#include "LoadStore.h"

#include "common.h"
#include "EffectPump.h"

class Result :  public QObject, public QGraphicsItem { // Temporal solution for results TODO make proper statistics analyzer
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    QRectF boundingRect() const {
        return QRectF(-VISUAL_SIZE, -VISUAL_SIZE, 2*VISUAL_SIZE, 2*VISUAL_SIZE);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool value;
};

class Scholar : public QMainWindow {
    Q_OBJECT
public:
    Scholar(AudioIO *audio, Mixer *mixer, SingleToneAnalyzer *sAna, ChordAnalyzer *chAna);
    virtual ~Scholar();
public slots:
    void ShowTuner();
    void DeleteTuner();
    void ShowAbout() { QMessageBox::about(this, QString("Guitar Learning Tool - About"), QString(AboutText)); }
    void ChangeBPMbySlider();
    void ChangeBPMbyText();
    void PlayStop();
    void OpenLesson();
    void ChangeVolume();
    void ChangeMetronomeState(bool);
    
    void ResizeSceneWidth(qreal nw) {
        scene->setSceneRect(0, 0, nw, scene->sceneRect().height());
    }
    
    void PostPreparation(); // A special function to do post-preparations, like carriage sync, etc.
    
    void FetchNote(Note* note);
    void SinglePitchData(bool result, double freq, int pitch, const char* note, double logPower);      // Show tune data itself
    void ChordData(float*, int);
    void CarriageFinished();
    
    // Passing to/from Tutor
    void StartTutor();
    void FetchFromTutor(Lesson*);
signals:
    void PassToTutor(Lesson*); // TODO create emit by view->switch to Tutor and vice-versa

protected:
    void RestartTimer();
    void closeEvent(QCloseEvent *event);
    //void DrawNotes();
private:
    Ui::Scholar widget;
    //Tutor *tutor;
    QGraphicsScene *scene;
    Carriage *carriage;
    unsigned bpm;         // BPM is binded with beat length: 1/4 -> each BPM length is for 1/4
    bool metronome_state;
    QTimer timer;
    QTimer post_preparation_timer; // A special timer to do post-preparations, like carriage sync, etc.
    
    Tuner *tuner;
    Metronome *metronome;
    EffectPump *effects;
    AudioIO *audio;
    Mixer *mixer;
    SingleToneAnalyzer *sAna;
    ChordAnalyzer *chAna;
    
    bool play_state; // true - playing, false - paused
    
    Lesson *lesson;
    Note* active_note;
    
    Result res;
};

#endif	/* _SCHOLAR_H */
