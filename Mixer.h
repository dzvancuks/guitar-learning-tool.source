/* 
 * File:   Mixer.h
 * Author: astral
 *
 * Created on 7 Декабрь 2012 г., 22:19
 */

// Credits to http://www.cplusplus.com/forum/general/77577/

#ifndef MIXER_H
#define	MIXER_H

#include <QTime>
#include <QMutex>
#include <QVector>
#include <math.h>
#include <assert.h>
//#include <QVector2D>

#include "AudioIO.h"
#include "common.h"

#define MAX_INPUTS 5
#define MAX_VECTOR_SIZE (16 * 1024) // 16K - maximum allowed for sound data passing

typedef enum AddSoundResultE {
    SUCCESS = 0, // successfully added sound vector
    WAIT,        // current cycle is ongoing; caller should wait, use queue, force queue or skip
    FULL,        // input vector is full; caller should wait, use queue, force queue or skip
    ERROR        // erroneous state, i.e. sample size mismatch
} AddSoundResult;

class Mixer : public QThread {
    Q_OBJECT
public:
    Mixer(AudioIO* audio);
    Mixer(const Mixer& orig);
    virtual ~Mixer();
    
    void SetGain(double g) { gain = MIN(g, 1); }
    AddSoundResult AddSound(QVector<float>& in, void* caller, bool trunked = false); // if caller ptr is present, ack it to wait or skip untill next cycle
    AddSoundResult QueueSound(QVector<float>& in, void* caller, bool trunked = false, bool override = false); // enqueue next sound data; if no data present, acts as AddSound
    AddSoundResult ForceSound(QVector<float>& in, void* caller, bool trunked = false); // queue and force ASAP 
    
public slots:
    void startProcess();
    void stopProcess();
private:
    void run();
private:
     bool m_abort;
     QMutex mutex; 
     
private:
    AudioIO* audio;
    typedef struct MixDataS {
        void *sender;         // a special ptr to track AddSound() callers: if ptr is present in input[], ack it to wait or skip untill next cycle
        float *data;  // any size < MAX_VECTOR_SIZE
        int data_size;
        float *queue; // vector to swap data with after data itself is finished
        int queue_size;
        int ptr;              // handled data beacon
        //QMutex processing;    // data vector lock
        bool force_swap;      // substitute data with queue ASAP; no need to wait for data vector to finish
    } MixData;
    QVector < MixData > input;
    QVector<float> output;
    int count; // actual buffer count of the input outer input array
    //QVector<void*> caller; // a special vector to track AddSound() callers: if ptr is present, ack it to wait or skip untill next cycle
    //unsigned long sequence; // 
    
    double gain; // loudness/volume. Set by slider in Scholar/Tutor. Values = [0.0, 1.0]
    
    // Sound mixing is executed every 1/(SAMPLE_RATE/AUDIO_BUF_SIZE) m. seconds; for 44,1KHz and 0.5K buffer, it is every 0.011 seconds
    //QTimer timer;
    int timeout;
    QMutex avalable; // access for new inputs
//private slots:
private: // slots:
    void ProcessQueue(MixData& data);
    void MixSounds();
    void OutputSounds();
    
    // TEST - PASS
    //QVector<float> test1;// (MAX_VECTOR_SIZE);
    //QVector<float> test2;// (MAX_VECTOR_SIZE);
//private slots:
    //void FetchSound(); // temp solution to test mixer & audio IO
};

#endif	/* MIXER_H */

