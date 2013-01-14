/* 
 * File:   EffectEcho.cpp
 * Author: astral
 * 
 * Created on 27 Декабрь 2012 г., 22:54
 */

#include "EffectEcho.h"

static int prime(int n) {
    int i;

    for(i=2; i<n; i++) 
        if(n % i == 0) 
                return 0;

    return 1;
}

EffectEcho::EffectEcho(QWidget *parent, QGridLayout *layout) : Effect(parent, layout, "Echo") {
    int i=10, j, k=0;
    
    echo_size=128;
    echo_decay=700;
    buffer_count=20;
    
    history.resize(buffer_count);
    index.resize(buffer_count);
    size.resize(buffer_count);
    factor.resize(buffer_count);
    
    while(k < buffer_count) {
        while(!prime(i))
            i++;
        i++;
        while(!prime(i))
            i++;
        factor[k]=i;
        k++;
        i++;
    }
    
    for(i = 0; i < buffer_count; i++) {
        size[i]=factor[i] * echo_size;
        history[i].resize(size[i]);
        for(j = 0; j < size[i]; j++)
            history[i][j]=0;
        index[i]=0;
    }
    
    QFont font;
    font.setPointSize(7);
    font.setWeight(15);
    
    decay_lbl = new QLabel(parent);
    decay_lbl->setObjectName(QString::fromUtf8("EchoDecayLabel"));
    decay_lbl->setEnabled(true);
    decay_lbl->setGeometry(QRect(0, TITLE_Y + 31, 30, 10));
    decay_lbl->setFont(font);
    decay_lbl->setAlignment(Qt::AlignLeft);
    decay_lbl->setText(QApplication::translate("EffectPump", "Decay", 0, QApplication::UnicodeUTF8));
    
    decay_val = new QLabel(parent);
    decay_val->setObjectName(QString::fromUtf8("EchoDecayValue"));
    decay_val->setEnabled(true);
    decay_val->setGeometry(QRect(FX_VISUAL_X - 20, TITLE_Y + 31, 20, 10));
    decay_val->setFont(font);
    decay_val->setAlignment(Qt::AlignLeft);
    decay_val->setText(QApplication::translate("EffectPump", QString::number(echo_decay).toAscii(), 0, QApplication::UnicodeUTF8));
    
    decay_slider = new QSlider(parent);
    decay_slider->setObjectName(QString::fromUtf8("EchoDecaySlider"));
    decay_slider->setGeometry(QRect(0, TITLE_Y + 41, FX_VISUAL_X, 10));
    decay_slider->setMinimum(0);
    decay_slider->setMaximum(1000);
    decay_slider->setSingleStep(20);
    decay_slider->setValue(echo_decay);
    decay_slider->setOrientation(Qt::Horizontal);
    QObject::connect(decay_slider, SIGNAL(valueChanged(int)), this, SLOT(Decay(int)));
    
    if (this->layout) {
        this->layout->addWidget(decay_lbl, 2, 0);
        this->layout->addWidget(decay_val, 2, 1);
        this->layout->addWidget(decay_slider, 3, 0, 2, 0); // with spanning
    }
}

EffectEcho::~EffectEcho() {
}

void EffectEcho::Process(QVector<float> *input) {
    int i=0, j;
    float sample;

    while(i < input->size()) {
        sample=input->at(i) * buffer_count;
        /* add sample, decay history */  
        for(j = 0; j < buffer_count; j++) {
            sample += 
                (history[j][index[j]] = history[j][index[j]] *
                        ((float)echo_decay /*+j*0*/)/1000 + input->at(i));
            index[j]++;
            if(index[j] >= size[j])
                index[j]=0;
        }
        sample=sample/2/(float)buffer_count;
        (*input)[i] = sample;

        i++;
    }
}
