/*
 * File:   main.cpp
 * Author: astral
 *
 * Created on 11 Июль 2012 г., 17:39
 */

#include <QtGui/QApplication>


#include "AudioIO.h"
#include "Mixer.h"
#include "SingleToneAnalyzer.h"
#include "ChordAnalyzer.h"
#include "Scholar.h"
#include "Tutor.h"

#include "LessonFile.pb.h"


int main(int argc, char *argv[]) {
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here

    AudioIO *audio = new AudioIO();
    Mixer *mixer = new Mixer(audio); mixer->startProcess();
    
    //Test
    //Metronome *metronome = new Metronome(mixer);
    
    SingleToneAnalyzer *sAna = new SingleToneAnalyzer(BUF_SIZE, SAMPLE_RATE, audio);
    //sAna->start(); // TODO started by Tuner and Scholar
    ChordAnalyzer *chAna = new ChordAnalyzer(BUF_SIZE, SAMPLE_RATE, audio);
    
    Scholar *scholar = new Scholar(audio, mixer, sAna, chAna);
    scholar->show(); // TODO started by Scholar

    Tutor *tutor = new Tutor(audio);
    //tutor->show();
    
    QObject::connect( scholar, SIGNAL(PassToTutor(Lesson*)), tutor, SLOT(FetchFromScholar(Lesson*)) );
    QObject::connect( tutor, SIGNAL(PassToScholar(Lesson*)), scholar, SLOT(FetchFromTutor(Lesson*)) );
    
    QObject::connect( &app, SIGNAL(lastWindowClosed()), audio, SLOT(Destroy()) ); // TODO same for sAna and chAna (?)
    QObject::connect( &app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()) );
    return app.exec();
}
