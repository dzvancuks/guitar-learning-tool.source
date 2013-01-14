/* 
 * File:   EffectPump.h
 * Author: astral
 *
 * Created on 25 Декабрь 2012 г., 19:44
 */

#ifndef EFFECTPUMP_H
#define	EFFECTPUMP_H

#include <QtGui/QtGui>
#include <QtGui/QFrame>
#include <QtGui/QComboBox>
#include "QVector"

#include "Effect.h"
#include "EffectDistortion.h"
#include "EffectEcho.h"

#include "AudioIO.h"
#include "Mixer.h"

#define AMPLIFY (2) // 2x is to amplify quiet electric guitar sound

typedef enum EffectTypesE {
    NONE = 0,
    DISTORTION,
    ECHO
}EffectTypes;

class EffectPump : public QWidget {
    Q_OBJECT
public:
    EffectPump(QWidget *parent = 0, AudioIO *audio = 0, Mixer *mixer = 0);
    EffectPump(const EffectPump& orig);
    virtual ~EffectPump();
    
    void SetAudio(AudioIO *audio) { this->audio = audio; }
    void SetMixer(Mixer *mixer) { this->mixer = mixer; }
    
public slots:
    void FetchSound(); // AidioIO InputReady() signal reaction
    
    void LoadEffect1(int i);
    void LoadEffect2(int i);
    void LoadEffect3(int i);
    
    void UnloadEffect1();
    void UnloadEffect2();
    void UnloadEffect3();
    
    void UnloadAllEffects();
    
private:
    AudioIO* audio;
    Mixer *mixer;
    
    QVector<float> data;
    bool processing;
    Effect *e1;
    Effect *e2;
    Effect *e3;
    
    void EnumerateEffects(QComboBox *list, int order);
    Effect * SelectionParser(int i, QWidget *parent, QGridLayout *layout);
    
    QFrame *effects_frame1;
    QFrame *effects_frame2;
    QFrame *effects_frame3;
    
    QWidget *effects_layout_widget1;
    QWidget *effects_layout_widget2;
    QWidget *effects_layout_widget3;
    QGridLayout *effects_layout1;
    QGridLayout *effects_layout2;
    QGridLayout *effects_layout3;
    
    QComboBox *effects_list1;
    QComboBox *effects_list2;
    QComboBox *effects_list3;
};

#endif	/* EFFECTPUMP_H */

