/*
 * File:   Tuner.cpp
 * Author: astral
 *
 * Created on 11 Июль 2012 г., 17:41
 */

#include "Tuner.h"

Tuner::Tuner() {
    audio = new AudioIO();
    sAna = new SingleToneAnalyzer(BUF_SIZE, SAMPLE_RATE, audio);
    
    TunerInit();
}

Tuner::Tuner(AudioIO* audio, SingleToneAnalyzer* analyzer) {
    this->audio = audio;
    this->sAna = analyzer;
    
    TunerInit();
}

Tuner::~Tuner() {
}


void Tuner::TunerInit(){
    unsigned int i;
    
    widget.setupUi(this);
    for (i = 0; i < (sizeof(InstrumentTypes)/sizeof(InstrumentType_t)); i++) {
        widget.TunerGuitarMenu->addItem(QString(InstrumentTypes[i].name));
    }
    
    connect(sAna, SIGNAL(sendAnalyzerData(bool, double, int, const char*, double)), this, SLOT(Tune(bool, double, int, const char*, double)));
    connect(widget.TunerDone, SIGNAL(clicked()), sAna, SLOT(stopProcess()));
    sAna->startProcess();
}

void Tuner::Tune(bool result, double freq, int pitch, const char* note, double logPower){
    if (result) {
        widget.TunerFreq->setText(QString::number(freq));
        widget.TunerNote->setText(QString(note));
    }
    //std::cout << "Got signal. Lol! \n";
    //std::cout << ", frq = " << freq << ", pitch = " << pitch << ", note = " << note << ", log = " << logPower << "\n";
}