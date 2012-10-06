/* 
 * File:   AudioIO.h
 * Author: astral
 *
 * Created on 24 Июль 2012 г., 20:35
 */

#ifndef AUDIOIO_H
#define	AUDIOIO_H

#include <QSemaphore>
#include <portaudio.h>
#include <vector>
//#include <queue>
//#include <list>
//#include <deque>
#include <iostream>

#define SAMPLE_RATE 44100
#define BUF_SIZE 1536 // bug from oTuner: 1k -> good pitch, does not see 6-th str; 2k -> see all strings, cant guess pitch propperly. Must analyze Tartini for solution.
#define IO_SAMPLE 512 // 256 = > ~5 ms. latency; ~2% CPU time; 512 => ~1ms, 1% CPU

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
    std::vector<float> input_copy1;      // first input buffer copy that proceeds to other processes
    std::vector<float> input_copy2;      // second input buffer copy that proceeds to other processes
    unsigned int input_count;            // data quantity in [input]
    QSemaphore input_lock1;              // semaphore lock for [input_copy1] during its copy process
    QSemaphore input_lock2;              // semaphore lock for [input_copy2] during its copy process
    unsigned int input_proceed_slot;     // points to [input_copy] buffer, that is safe to (and should be) read; 1 or 2
    
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

class AudioIO {
public:
    AudioIO();
    virtual ~AudioIO();
    /*
     * This can't be used due to use of 'patestCallback' function pointer callback, instead of 'AudioIO::patestCallback'
    int patestCallback( const void *inputBuffer, void *outputBuffer,
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData );
     */
    paUserData* GetPaDataPtr() {return &data;}; // Yes, this is stupid. Nees some lock mechanisms
    // some safe implementation to avoid use of internal data for interrupst
    std::vector<float>& GetInput_safe() 
        { return (data.input_proceed_slot == 1 ? data.input_copy1 : data.input_copy2);}
private:
    PaStream *stream;
    PaError err;
    paUserData data; // TODO malloc'ed
};

#endif	/* AUDIOIO_H */

