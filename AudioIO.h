/* 
 * File:   AudioIO.h
 * Author: astral
 *
 * Created on 24 Июль 2012 г., 20:35
 */

#ifndef AUDIOIO_H
#define	AUDIOIO_H

#include <QtCore/QtCore>
#include <QSemaphore>
#include "QTimer"
#include <portaudio.h>
#include <vector>
//#include <queue>
//#include <list>
//#include <deque>
#include <iostream>

#include "common.h"

#define SAMPLE_RATE 44100
#define BUF_SIZE 2048 // bug from oTuner: 1k -> good pitch, does not see 6-th str; 2k -> see all strings, cant guess pitch propperly. Must analyze Tartini for solution.
#define IO_SAMPLE 512 // 256 = > ~5 ms. latency, ~2% CPU time; 512 => ~1ms, 1% CPU
#define AUDIO_BUF_SIZE (4*IO_SAMPLE) // TODO find a way to shrink it!
#define TIMER_CHECK_MS (1000 / ((SAMPLE_RATE) /(IO_SAMPLE/4)) )

/* 'Global' critical resource for input/output operations.
 * Other processes should use ONLY:
 * input_copyN        - input data (copy). Using 2 alternating buffers.
 * input_proceed_slot - points out which [input_copyN] is safe to read
 * input_lockN        - semaphore lock for [input_copyN]; lockes INTERNALLY, only to inform.
 *                      External process should use available() function without locking.
 * output             - data to output
 * output_lock        - semaphore lock for [output]
 * Every other item is for AudioIO use only
 */
typedef struct
{
    /* Input is constantlu filled with input data. When input_count reaches window maximum,
     * it should copy out data into [input_proceedN] (locked by semapthore during this process).
     * New input data is overwritten into [input] from beginning.
     * 
     * There is a chance that [input_proceed] will be corrupted.
     * 
     * All is done due to lack of robusntess to long-term interrupts by PortAudio.
     */
    std::vector<float> input;            // input buffer itself
    std::vector<float> input_copy1;      // first input buffer copy that proceeds to other processes (2K)
    std::vector<float> input_copy2;      // second input buffer copy that proceeds to other processes
    std::vector<float> input_copy1_extended;      // same as above, but uses doubled amount of data - 4K...
    std::vector<float> input_copy2_extended;      // ... filled by every input_copy1 and input_copy2 input loop
    std::vector<float> input_copy1_sound;      // same as above, but uses shrink amount of data for ACTUAL sound processing - 0.5K...
    std::vector<float> input_copy2_sound;      // ... filled by every input_copy1 and input_copy2 input loop
    unsigned int input_count;            // data quantity in [input]
    QSemaphore input_lock1;              // semaphore lock for [input_copy1] during its copy process
    QSemaphore input_lock2;              // semaphore lock for [input_copy2] during its copy process
    QSemaphore input_lock1_extended;     // same as above, used by extended buffers
    QSemaphore input_lock2_extended;
    QSemaphore input_lock1_sound;     // same as above, used by sound buffers
    QSemaphore input_lock2_sound;
    unsigned int input_proceed_slot;     // points to [input_copy] buffer, that is safe to (and should be) read; 1 or 2
    unsigned int input_proceed_slot_extended; // same as above, used by extended buffers
    unsigned int input_proceed_slot_sound; // same as above, used by sound buffers
    
    /* When data is ready to be sent to output, it is loaded into [output];
     * output_loaded = output data length;
     * output_processed = 0, i.e. beginning of the [output];
     * [output] becomes locked.
     * Each callback iteration, process small portion of [output], shifting output_processed:
     * [.......................................................................]
     *                    ^                                                   ^
     * (proocerssed data) |                (pending data)                     |
     *              output_processed                                    output_loaded
     * 
     * Special [output_unlocked] buffer contains last used chunk of of oginal [output].
     * Used to prevent sound gaps, when the original [output] is free to be used by other process.
     */
    std::vector<float> output;           // output buffer itself
    std::vector<float> output_unlocked;  // output buffer size of frames; contains last output data in case [output] is locked
    unsigned int output_loaded;          // data quantity in [output]
    unsigned int output_processed;       // data quantity processed to speakers
    QSemaphore output_lock;
}
paUserData;

int patestCallback( const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData );

class AudioIOException
{
private:
    std::string m_strError;
    PaError m_err;
 
    AudioIOException() {}; // not meant to be called
public:
    AudioIOException(std::string strError, PaError paErr)
        : m_strError(strError), m_err(paErr)
    {
    }
 
    std::string GetErrorName() { return m_strError; }
    int GetErrorCode() { return m_err; }
};

class AudioIO : public QObject {
    Q_OBJECT
public:
    AudioIO();
    //AudioIO(const AudioIO& orig);
    virtual ~AudioIO();
    
    paUserData* GetPaDataPtr() {return &data;}; // Yes, this is stupid. Use GetInput_safe() with some lock mechanisms
    
    // some safe implementation to avoid use of internal data for interrupts
    std::vector<float>& GetInput_safe() 
        { return (data.input_proceed_slot == 1 ? data.input_copy1 : data.input_copy2); }
    // GetExtendedInput_safe() is used to fetch 4K data, instead of quick 2K; used by ChordAna
    std::vector<float>& GetExtendedInput_safe()
        { return (data.input_proceed_slot_extended == 1 ? data.input_copy1_extended : data.input_copy2_extended); }
    // GetSoundInput_safe() is used to fetch ???K data, instead of delayed 2K; used by Effects and Mixer
    std::vector<float>& GetSoundInput_safe()
        { return (data.input_proceed_slot_sound == 1 ? data.input_copy1_sound : data.input_copy2_sound); }
    
    void SetOutput(std::vector<float>& in);
    //static void SignalInputReady() { emit InputReady(); }
signals:
    void InputReady(); // every class, receiving this signal, should try to GetInput_safe(), if ready

public slots:
    void Destroy() { this->~AudioIO(); } // used on app close
private:
    PaStream *stream;
    PaError err;
    paUserData data; // TODO malloc'ed
    
    // "data ready" routine
    unsigned int last_ready_buffer;
    QTimer timer;
private slots:
    void Timeout();
};

#endif	/* AUDIOIO_H */

