/* 
 * File:   EffectEcho.h
 * Author: astral
 *
 * Created on 27 Декабрь 2012 г., 22:54
 */

#ifndef EFFECTECHO_H
#define	EFFECTECHO_H

#include "Effect.h"

class EffectEcho : public Effect {
    Q_OBJECT
public:
    EffectEcho(QWidget *parent = 0, QGridLayout *layout = 0);
    virtual ~EffectEcho();
    
public slots:
    virtual void Process(QVector<float> *input);
    
    void Decay(int d) { echo_decay = d; decay_val->setText(QString::number(echo_decay)); }
    
private:
    int echo_size, echo_decay, buffer_count;
    QVector< QVector<float> > history;
    QVector <int> index, size, factor;
    
    // Visuals
    QSlider *decay_slider; // rewrite for echo_size, echo_decay
    QLabel *decay_lbl;
    QLabel *decay_val;
};

#endif	/* EFFECTECHO_H */

