/*
 * File:   main.cpp
 * Author: astral
 *
 * Created on 11 Июль 2012 г., 17:39
 */

#include <QtGui/QApplication>

#include "Scholar.h"
#include "AudioIO.h"
#include "SingleToneAnalyzer.h"

int main(int argc, char *argv[]) {
    // initialize resources, if needed
    // Q_INIT_RESOURCE(resfile);

    QApplication app(argc, argv);

    // create and show your widgets here

    AudioIO *audio = new AudioIO();
    //audio->run();
    //sleep(100); // to initially fill input buffers
    SingleToneAnalyzer *sAna = new SingleToneAnalyzer(BUF_SIZE, SAMPLE_RATE, audio);
    Scholar *scholar = new Scholar(audio, sAna); //, chAna);
    
    //QThread *sAnaThread = new QThread;
    //QObject::connect(scholar, SIGNAL(getSingleTone()), sAna, SLOT(run()));
    //sAna->moveToThread(sAnaThread);
    //sAnaThread->start();
    sAna->start();
    //sAna->wait(); // move to Scholar destructor??
    
    /*
     * ChordAnalyzer *chAna = new ChordAnalyzer(BUF_SIZE, SAMPLE_RATE, audio);
     */

    scholar->show();

    QObject::connect( &app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()) );
    return app.exec();
}
