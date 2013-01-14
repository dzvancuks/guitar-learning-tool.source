/* 
 * File:   EffectDistortion.h
 * Author: astral
 *
 * Created on 26 Декабрь 2012 г., 16:24
 */

#ifndef EFFECTDISTORTION_H
#define	EFFECTDISTORTION_H

#include "Effect.h"
#include "common.h" // debug use only

class EffectDistortion : public Effect {
    Q_OBJECT
public:
    EffectDistortion(QWidget *parent = 0, QGridLayout *layout = 0);
    virtual ~EffectDistortion();
    
public slots:
    void Level(int l) { level = l; level_val->setText(QString::number(level)); }
    //void Threshhold(float t) { treshold = t; treshold_val->setText(QString::number(treshold*100)); }
    //void ThreshholdBySlider(int t) { treshold = (float)t/100.; treshold_val->setText(QString::number(t)); }
    //void Freq(float f) { freq = f; }
    void Cutoff(float c) { cutoff = c; }
    void CutoffBySlider(int c) { cutoff = (float)c; co_val->setText(QString::number(cutoff)); RC_set_freq(cutoff, &lpf); }
    //void NoiseGate(float ng) { noise_gate = ng; ng_val->setText(QString::number(noise_gate*100)); }
    //void NoiseGateBySlider(int ng) { noise_gate = (float)ng/100.; ng_val->setText(QString::number(ng)); }

public slots:
    virtual void Process(QVector<float> *input);
    
private:
    float level;
    float threshold;

    float freq;
    struct filter_data lcf;

    float cutoff;
    struct filter_data lpf;

    float noise_gate;
    
    // Visuals
    QSlider *level_slider;
    QLabel *level_lbl;
    QLabel *level_val;
    /*
    QSlider *treshold_slider;
    QLabel *treshold_lbl;
    QLabel *treshold_val;
    QSlider *ng_slider;
    QLabel *ng_lbl;
    QLabel *ng_val;
    */
    QSlider *co_slider;
    QLabel *co_lbl;
    QLabel *co_val;
};

#endif	/* EFFECTDISTORTION_H */

