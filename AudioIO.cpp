/* 
 * File:   AudioIO.cpp
 * Author: astral
 * 
 * Created on 24 Июль 2012 г., 20:35
 */

#include "AudioIO.h"

AudioIO::AudioIO() : QObject(NULL) {
    data.input.resize(BUF_SIZE);
    data.input_copy1.resize(BUF_SIZE);
    data.input_copy2.resize(BUF_SIZE);
    data.input_copy1_extended.resize(BUF_SIZE*2);
    data.input_copy2_extended.resize(BUF_SIZE*2);
    data.input_copy1_sound.resize(AUDIO_BUF_SIZE);
    data.input_copy2_sound.resize(AUDIO_BUF_SIZE);
    data.input_proceed_slot = 1;
    data.input_proceed_slot_extended = 1;
    data.input_proceed_slot_sound = 1;
    data.input_count = 0;
    
    data.output.resize(AUDIO_BUF_SIZE);
    data.output_unlocked.resize(IO_SAMPLE);
    data.output_loaded = 0;
    data.output_processed = 0;
    
    data.input_lock1.release();
    data.input_lock2.release();
    data.input_lock1_extended.release();
    data.input_lock2_extended.release();
    data.input_lock1_sound.release();
    data.input_lock2_sound.release();
    data.output_lock.release();
    
    last_ready_buffer = data.input_proceed_slot;
    
    try {
        err = Pa_Initialize();
        if( err != paNoError ) {
            throw AudioIOException("Pa_Initialize()", err);
        }

        err = Pa_OpenDefaultStream( &stream,
                                    2,          /* 2 input channels: mic + line in */
                                    2,          /* stereo output */
                                    paFloat32,  /* 32 bit floating point output */
                                    SAMPLE_RATE,/* 44100 */
                                    IO_SAMPLE,  /* Frames/buffer */
                                    patestCallback, /* callback function (global?) */
                                    &data ); /* This is a pointer passed to callback*/
        if( err != paNoError ) {
            Pa_Terminate();
            throw AudioIOException("Pa_OpenDefaultStream()", err);
        }

        err = Pa_StartStream( stream );
        if( err != paNoError ) {
            Pa_CloseStream( stream );
            Pa_Terminate();
            throw AudioIOException("Pa_StartStream()", err);
        }
    }
    catch (AudioIOException &aioExc) {
        std::cout << "PortAudio " << aioExc.GetErrorName() << " error: " << Pa_GetErrorText( aioExc.GetErrorCode() ) << "\n";
    }
    
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(Timeout()));
    timer.setSingleShot(false); // infinite loop
    //timer.setInterval(TIMER_CHECK_MS);
    timer.start(TIMER_CHECK_MS);
}

void AudioIO::Timeout() {
    if (data.input_proceed_slot != last_ready_buffer) {
        last_ready_buffer = data.input_proceed_slot;
        emit InputReady();
    }
}

AudioIO::~AudioIO() {
    timer.stop();
    
    try {
        err = Pa_StopStream( stream );
        if( err != paNoError ) {
            Pa_CloseStream( stream ); // just try if possible
            Pa_Terminate();
            throw AudioIOException("Pa_StopStream()", err);
        }

        err = Pa_CloseStream( stream );
        if( err != paNoError ) {
            Pa_Terminate();
            throw AudioIOException("Pa_CloseStream()", err);
        }

        err = Pa_Terminate();
        if( err != paNoError ) {
            throw AudioIOException("Pa_Terminate()", err);
        }
    }
    catch (AudioIOException &aioExc){
        std::cerr << "PortAudio " << aioExc.GetErrorName() << " error: " << Pa_GetErrorText( aioExc.GetErrorCode() ) << "\n";
    }
}

void AudioIO::SetOutput(std::vector<float>& in) {
    data.output_lock.acquire();
    
    data.output_loaded = MIN(AUDIO_BUF_SIZE, in.size());
    for (unsigned i = 0; i < data.output_loaded; i++) {
        data.output[i] = in[i];
    }
    data.output_processed = 0;
    
    data.output_lock.release();
    
    // TEST
    //std::cout << "Got output!\n"; //- Passed!
}

int patestCallback( const void *inputBuffer, void *outputBuffer, //test only
                        unsigned long framesPerBuffer,
                        const PaStreamCallbackTimeInfo* timeInfo,
                        PaStreamCallbackFlags statusFlags,
                        void *userData ){
    //(void)userData; /* Prevent unused variable warning. */
    paUserData *data = (paUserData*)userData;
    (void)timeInfo;
    (void)statusFlags;
    float *in = (float*)inputBuffer;
    float *out = (float*)outputBuffer;
    unsigned int i;
    
    for(i = 0; i < framesPerBuffer; i++) {
        data->input[data->input_count + i] = *in;
        in += 2; // mono input from sterio line-in
        ////data->input_count++;

        //Temporal solution. TODO use mixer object
        //data->output[data->input_count + i] = data->input[data->input_count + i] * 2;
        
        ////data->output[i*2 + 1] = data->input[i*2 + 1];//.insert(data->it_out++, *tmp_in++);

        // TODO make use of [output_unlocked]
        if (data->output_processed  <= BUF_SIZE - framesPerBuffer && data->output_lock.available()) {
            *out++ = data->output[data->output_processed + i];
            *out++ = data->output[data->output_processed + i]; // stereo
            data->output_unlocked[i] = data->output[data->output_processed + i];
        } else {
            *out++ = data->output_unlocked[i];
            *out++ = data->output_unlocked[i]; // stereo
        }
    }
    data->input_count += framesPerBuffer;
    data->output_processed += ( data->output_processed  <= BUF_SIZE - framesPerBuffer ? framesPerBuffer : 0 );
    //std::cout << "Processed out\n";
    
    // Sound data for sound processing classes: effects, mixer, etc.
    if (data->input_count >= AUDIO_BUF_SIZE && data->input_count % AUDIO_BUF_SIZE == 0) {
        unsigned offset = data->input_count - AUDIO_BUF_SIZE;
        if (data->input_proceed_slot_sound == 1) { // 1-st is filled and ready to be proceed; buf #2 gets filled
            data->input_lock2_sound.acquire();
            for (i = 0; i < AUDIO_BUF_SIZE; i++) { // make MACRO function
                data->input_copy2_sound[i] = data->input[offset + i];
            }
            data->input_lock2_sound.release();
        } else {
            data->input_lock1_sound.acquire();
            for (i = 0; i < AUDIO_BUF_SIZE; i++) {
                data->input_copy1_sound[i] = data->input[offset + i];
            }
            data->input_lock1_sound.release();
        }
        data->input_proceed_slot_sound = 3 - data->input_proceed_slot_sound; // result = 1 or 2
        //std::cout << "Prepared " << data->input_proceed_slot_sound << " in-buffer\n";
    }
    
    // Sound data for analysers
    if (data->input_count >= BUF_SIZE) {
        // 2K buffer
        if (data->input_proceed_slot == 1) { // 1-st is filled and ready to be proceed; buf #2 gets filled
            data->input_lock2.acquire();
            for (i = 0; i < BUF_SIZE; i++) { // make MACRO function
                data->input_copy2[i] = data->input[i];
            }
            data->input_lock2.release();
        } else {
            data->input_lock1.acquire();
            for (i = 0; i < BUF_SIZE; i++) {
                data->input_copy1[i] = data->input[i];
            }
            data->input_lock1.release();
        }
        data->input_proceed_slot = 3 - data->input_proceed_slot; // result = 1 or 2
        
        // 4k buffer
        if (data->input_proceed_slot_extended == 1) { // 1-st is filled and ready to be proceed; buf #2 gets filled
            if (data->input_proceed_slot == 1) { // buf #1 is ready to be proceeded: lock extended until it is filled with data from both buffers
                data->input_lock2_extended.acquire();
                for (i = 0; i < BUF_SIZE; i++) { // make MACRO function
                    data->input_copy2_extended[i] = data->input_copy1[i];
                }
                //std::cout << "\nOLOLO 1\n";
            } else {
                for (i = 0; i < BUF_SIZE; i++) { // make MACRO function
                    data->input_copy2_extended[i] = data->input_copy2[i];
                }
                data->input_lock2_extended.release();
                data->input_proceed_slot_extended = 3 - data->input_proceed_slot_extended; // result = 1 or 2
                ///std::cout << "\nOLOLO 2\n";
            }
        } else {
            if (data->input_proceed_slot == 1) { // buf #1 is ready to be proceeded: lock extended until it is filled with data from both buffers
                data->input_lock1_extended.acquire();
                for (i = 0; i < BUF_SIZE; i++) { // make MACRO function
                    data->input_copy1_extended[i] = data->input_copy1[i];
                }
                ///std::cout << "\nOLOLO 3\n";
            } else {
                for (i = 0; i < BUF_SIZE; i++) { // make MACRO function
                    data->input_copy1_extended[i] = data->input_copy2[i];
                }
                data->input_lock1_extended.release();
                data->input_proceed_slot_extended = 3 - data->input_proceed_slot_extended; // result = 1 or 2
                //std::cout << "\nOLOLO 4\n";
            }
        }

        data->input_count = 0;
        //AudioIO::SignalInputReady();
    }
    
    return 0;
}

