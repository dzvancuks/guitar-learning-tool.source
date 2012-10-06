/* 
 * File:   AudioIO.cpp
 * Author: astral
 * 
 * Created on 24 Июль 2012 г., 20:35
 */

#include "AudioIO.h"

AudioIO::AudioIO() {
    data.input.resize(BUF_SIZE);
    data.input_copy1.resize(BUF_SIZE);
    data.input_copy2.resize(BUF_SIZE);
    data.input_proceed_slot = 1;
    data.input_count = 0;
    
    data.output.resize(BUF_SIZE);
    data.output_unlocked.resize(IO_SAMPLE);
    data.output_loaded = 0;
    data.output_processed = 0;
    
    data.input_lock1.release();
    data.input_lock2.release();
    
    

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
}

AudioIO::~AudioIO() {
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
        /*
        std::cout << *in << "\n";
        *out++ = *in * 4;
        *out++ = *in * 4;
        in += 2;
        /*/
        data->input[data->input_count + i] = *in;
        //data->input[i*2 + 1] = *in;
        in += 2; // mono input from sterio line-in
        //data->input_count++;

        //Temporal solution. TODO use mixer object
        data->output[data->input_count + i] = data->input[data->input_count + i] * 4;
        //data->output[i*2 + 1] = data->input[i*2 + 1];//.insert(data->it_out++, *tmp_in++);

        // TODO make use of [output_unlocked]
        *out++ = data->output[data->input_count + i];
        *out++ = data->output[data->input_count + i];
        
    }
    data->input_count += framesPerBuffer; // minor optimization
    
    if (data->input_count >= BUF_SIZE) {
        if (data->input_proceed_slot == 1) {
            data->input_lock2.acquire();
            for (i = 0; i < BUF_SIZE; i++) { // make MACRO function
                data->input_copy2[i] = data->input[i*2];
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
        data->input_count = 0;
    }
    
    return 0;
}

