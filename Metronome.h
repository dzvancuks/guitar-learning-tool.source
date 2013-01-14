/* 
 * File:   Metronome.h
 * Author: astral
 *
 * Created on 16 Декабрь 2012 г., 21:26
 */

#ifndef METRONOME_H
#define	METRONOME_H

#include "QFile"
//#include "QtMultimedia/QtMultimedia"
//#include "QtMultimedia/QAudioFormat"
#include "QVector"
#include "QByteArray"
#include "QDataStream"
#include <limits>

#include "Mixer.h"
//#include "common.h"

class Metronome : public QObject {//: public QThread {
    Q_OBJECT
public:
    Metronome(Mixer *mixer);
    Metronome(const Metronome& orig);
    virtual ~Metronome();

    void SetSoundType(QString type); // using resources
    void SetInterval(int i) { interval = i; }
    void Start() { time.restart(); timer.start(interval); } // clean start
    void Stop() { timer.stop(); }

    /* // use SIGNAL(timeout()) instead
// Thread routine
public slots:
    void startProcess();
    void stopProcess();
private:
    void run();
private:
     bool m_abort;
     QMutex mutex; 
   */ 
     
public slots:
    void Sync(); // sync metronome with each new Bar: force reset timer
private slots:
    void OutputSound();   // push sound into Mixer
    
private:
    void GenerateSound(); // parse file data (wav/pcm) into vector
    void InterpolateInput();
    ////void OutputSound();   // push sound into Mixer
    Mixer *mixer;
    QTimer timer;    // timer to ignore note passing
    QTime time;      // for timer adjustment
    bool ignore_timeout; // ignore time.restart() on sync()
    int interval;
    
    typedef struct MetadataS{
        int data_size;
        int sample_rate;
        int sample_size;
        int channel_count;
    } Metadata;
    
    QFile f;
    QByteArray input_data;          // raw, any bitrate
    //QAudioFormat input_format;      // used only as internal metadata!
    Metadata input_format;
    QVector<float> output_data_all; // 44KHz, float, interpolated from input_data
    //QAudioFormat output_format;     // used only as internal metadata!
    Metadata output_format;
    int pos; // position in output_data_all to read next data chunk
    QVector<float> output_data;     // 44KHz, float, AUDIO_BUF_SIZE, ready to write to Mixer
};

#endif	/* METRONOME_H */

