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

#include "ui_Scholar.h"
#include "Tuner.h"
#include "Lesson.h"
#include "Carriage.h"

class Result : public QGraphicsItem { // Temporal solution for results
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
    Scholar(AudioIO *audio, SingleToneAnalyzer *sAna);
    virtual ~Scholar();
public slots:
    void ShowTuner();
    void ChangeBPMbySlider();
    void ChangeBPMbyText();
    void PlayStop();
    void OpenLesson();
    //void getSingleTone(){};
    
    void ResizeSceneWidth(qreal nw) {
        scene->setSceneRect(0, 0, nw, scene->sceneRect().height());
    }
    
    void PostPreparation(); // A special function to do post-preparations, like carriage sync, etc.
    
    void FetchNote(Note* note);
    void SinglePitchData(bool result, double freq, int pitch, const char* note, double logPower);      // Show tune data itself
    void CarriageFinished();
protected:
    void RestartTimer();
    void closeEvent(QCloseEvent *event);
    void DrawNotes();
private:
    Ui::Scholar widget;
    QGraphicsScene *scene;
    Carriage *carriage;
    unsigned bpm;         // Assume, that 1 beat is 1/4
    QTimer timer;
    QTimer post_preparation_timer; // A special timer to do post-preparations, like carriage sync, etc.
    
    Tuner *tuner;
    AudioIO *audio;
    SingleToneAnalyzer *sAna;
    //ChordAnalyzer *chAna;
    
    bool play_state; // true - playing, false - paused
    
    Lesson *lesson;
    Note* active_note;
    
    Result res;
};

#endif	/* _SCHOLAR_H */
