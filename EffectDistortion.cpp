/* 
 * File:   EffectDistortion.cpp
 * Author: astral
 * 
 * Created on 26 Декабрь 2012 г., 16:24
 */

#include "EffectDistortion.h"

EffectDistortion::EffectDistortion(QWidget *parent, QGridLayout *layout) : Effect(parent, layout, "Distortion") {
    // Default values
    level = 260;
    threshold = 0.4; //5000;
    noise_gate = 0.1; // 2000;
    
    // Filter
    freq = 800.0;
    cutoff = 3000.0;
    
    RC_setup(5, 1.0, &lcf);
    //  RC_set_freq(22000.0, &(p->lcf));

    RC_setup(5, 1.0, &lpf);
    RC_set_freq(cutoff, &lpf);
    
    QFont font;
    font.setPointSize(7);
    font.setWeight(15);
    
    level_lbl = new QLabel(parent);
    level_lbl->setObjectName(QString::fromUtf8("DistortionLevelLabel"));
    level_lbl->setEnabled(true);
    //level_lbl->setGeometry(QRect(0, TITLE_Y + 31, 30, 10));
    level_lbl->setFont(font);
    level_lbl->setAlignment(Qt::AlignLeft);
    level_lbl->setText(QApplication::translate("EffectPump", "Level", 0, QApplication::UnicodeUTF8));
    
    level_val = new QLabel(parent);
    level_val->setObjectName(QString::fromUtf8("DistortionLevelValue"));
    level_val->setEnabled(true);
    //level_val->setGeometry(QRect(FX_VISUAL_X - 20, TITLE_Y + 31, 20, 10));
    level_val->setFont(font);
    level_val->setAlignment(Qt::AlignLeft);
    level_val->setText(QApplication::translate("EffectPump", QString::number(level).toAscii(), 0, QApplication::UnicodeUTF8));
    
    level_slider = new QSlider(parent);
    level_slider->setObjectName(QString::fromUtf8("DistortionLevelSlider"));
    //level_slider->setGeometry(QRect(0, TITLE_Y + 41, FX_VISUAL_X, 10));
    level_slider->setMinimum(100);
    level_slider->setMaximum(500);
    level_slider->setSingleStep(10);
    level_slider->setValue(level);
    level_slider->setOrientation(Qt::Horizontal);
    QObject::connect(level_slider, SIGNAL(valueChanged(int)), this, SLOT(Level(int)));
    
    /*
    treshold_lbl = new QLabel(parent);
    treshold_lbl->setObjectName(QString::fromUtf8("DistortionTresholdLabel"));
    treshold_lbl->setEnabled(true);
    treshold_lbl->setGeometry(QRect(0, TITLE_Y + 41, 40, 10));
    treshold_lbl->setFont(font);
    treshold_lbl->setAlignment(Qt::AlignLeft);
    treshold_lbl->setText(QApplication::translate("EffectPump", "Treshold", 0, QApplication::UnicodeUTF8));
    
    treshold_val = new QLabel(parent);
    treshold_val->setObjectName(QString::fromUtf8("DistortionTresholdValue"));
    treshold_val->setEnabled(true);
    treshold_val->setGeometry(QRect(FX_VISUAL_X - 20, TITLE_Y + 41, 20, 10));
    treshold_val->setFont(font);
    treshold_val->setAlignment(Qt::AlignLeft);
    treshold_val->setText(QApplication::translate("EffectPump", QString::number(treshold*100).toAscii(), 0, QApplication::UnicodeUTF8));
    
    treshold_slider = new QSlider(parent);
    treshold_slider->setObjectName(QString::fromUtf8("DistortionSlider"));
    treshold_slider->setGeometry(QRect(0, TITLE_Y + 51, FX_VISUAL_X, 10));
    treshold_slider->setMinimum(10);
    treshold_slider->setMaximum(100);
    treshold_slider->setSingleStep(5);
    treshold_slider->setValue(treshold * 100);
    treshold_slider->setOrientation(Qt::Horizontal);
    QObject::connect(treshold_slider, SIGNAL(valueChanged(int)), this, SLOT(ThreshholdBySlider(int)));
    
    ng_lbl = new QLabel(parent);
    ng_lbl->setObjectName(QString::fromUtf8("DistortionNoiseGateLabel"));
    ng_lbl->setEnabled(true);
    ng_lbl->setGeometry(QRect(0, TITLE_Y + 61, 45, 10));
    ng_lbl->setFont(font);
    ng_lbl->setAlignment(Qt::AlignLeft);
    ng_lbl->setText(QApplication::translate("EffectPump", "NoiseGate", 0, QApplication::UnicodeUTF8));
    
    ng_val = new QLabel(parent);
    ng_val->setObjectName(QString::fromUtf8("DistortionNoiseGateValue"));
    ng_val->setEnabled(true);
    ng_val->setGeometry(QRect(FX_VISUAL_X - 20, TITLE_Y + 61, 20, 10));
    ng_val->setFont(font);
    ng_val->setAlignment(Qt::AlignLeft);
    ng_val->setText(QApplication::translate("EffectPump", QString::number(noise_gate*100).toAscii(), 0, QApplication::UnicodeUTF8));
    
    ng_slider = new QSlider(parent);
    ng_slider->setObjectName(QString::fromUtf8("NoiseGateSlider"));
    ng_slider->setGeometry(QRect(0, TITLE_Y + 71, FX_VISUAL_X, 10));
    ng_slider->setMinimum(0);
    ng_slider->setMaximum(50);
    ng_slider->setSingleStep(5);
    ng_slider->setValue(noise_gate * 100);
    ng_slider->setOrientation(Qt::Horizontal);
    QObject::connect(ng_slider, SIGNAL(valueChanged(int)), this, SLOT(NoiseGateBySlider(int)));
    */
     
    co_lbl = new QLabel(parent);
    co_lbl->setObjectName(QString::fromUtf8("DistortionCutoffLabel"));
    co_lbl->setEnabled(true);
    //co_lbl->setGeometry(QRect(0, TITLE_Y + 61, 45, 10));
    co_lbl->setFont(font);
    co_lbl->setAlignment(Qt::AlignLeft);
    co_lbl->setText(QApplication::translate("EffectPump", "Cutoff", 0, QApplication::UnicodeUTF8));
    
    co_val = new QLabel(parent);
    co_val->setObjectName(QString::fromUtf8("DistortionCutoffValue"));
    co_val->setEnabled(true);
    //co_val->setGeometry(QRect(FX_VISUAL_X - 20, TITLE_Y + 61, 20, 10));
    co_val->setFont(font);
    co_val->setAlignment(Qt::AlignLeft);
    co_val->setText(QApplication::translate("EffectPump", QString::number(cutoff).toAscii(), 0, QApplication::UnicodeUTF8));
    
    co_slider = new QSlider(parent);
    co_slider->setObjectName(QString::fromUtf8("CutoffSlider"));
    //co_slider->setGeometry(QRect(0, TITLE_Y + 71, FX_VISUAL_X, 10));
    co_slider->setMinimum(500);
    co_slider->setMaximum(5000);
    co_slider->setSingleStep(500);
    co_slider->setValue((int)cutoff);
    co_slider->setOrientation(Qt::Horizontal);
    QObject::connect(co_slider, SIGNAL(valueChanged(int)), this, SLOT(CutoffBySlider(int)));
    
    if (this->layout) {
        this->layout->addWidget(level_lbl, 2, 0);
        this->layout->addWidget(level_val, 2, 1);
        this->layout->addWidget(level_slider, 3, 0, 2, 0); // with spanning
        
        this->layout->addWidget(co_lbl, 4, 0);
        this->layout->addWidget(co_val, 4, 1);
        this->layout->addWidget(co_slider, 5, 0, 2, 0);
    }
}

EffectDistortion::~EffectDistortion() {
    while (layout->count()) {
        QWidget *w = layout->itemAt(0)->widget();
        layout->removeItem(layout->itemAt(0));
        delete w;
    }
}

void EffectDistortion::Process(QVector<float> *input) {
    //ARR_DBUG1(*input);
    LC_filter(input, 0, freq, &lcf);
    
    
    //clip
    for(int i = 0; i < input->size(); i++) {
        (*input)[i] *= level;
        if((*input)[i] > threshold)
            (*input)[i] = threshold;
        else if((*input)[i] < -threshold)
            (*input)[i] = -threshold;

        // noise gate
        if(fabsf((*input)[i]) < noise_gate)
            (*input)[i] = 0;
    }

    // lowpass filter
    RC_lowpass(input, &lpf);
    //ARR_DBUG2(*input);
}
