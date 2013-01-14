/* 
 * File:   Mixer.cpp
 * Author: astral
 * 
 * Created on 7 Декабрь 2012 г., 22:19
 */

#include "Mixer.h"

Mixer::Mixer(AudioIO* audio) {
    this->audio = audio;
    
    //caller = QVector<void*>(MAX_INPUTS);
    
    input = QVector < MixData > (MAX_INPUTS);
    for(int i = 0; i < input.size(); i++) {
        //input[i].resize(AUDIO_BUF_SIZE);
        //input[i].processing.unlock();
        input[i].ptr = 0;
        input[i].force_swap = false;
        input[i].sender = NULL;
        input[i].data = new float[MAX_VECTOR_SIZE];
        input[i].data_size = 0;
        input[i].queue = new float[MAX_VECTOR_SIZE];
        input[i].queue_size = 0;
    }
    count = 0;
    
    output = QVector<float>(AUDIO_BUF_SIZE);
    
    gain = 0.5;
    
    timeout = 1000/(SAMPLE_RATE/AUDIO_BUF_SIZE);
    //QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(MixSounds()));
    //timer.start( 1000/(SAMPLE_RATE/AUDIO_BUF_SIZE) );
    
    // TEST
    //assert ( QObject::connect(audio, SIGNAL(InputReady()), this, SLOT(FetchSound())) ); // - to effects
    /* - Passed
    test1.resize(MAX_VECTOR_SIZE - 500);
    test2.resize(MAX_VECTOR_SIZE - 500);
    for (int i = 0; i < MAX_VECTOR_SIZE - 500; i++) {
        test1[i] = (float) (0.5 * sin( ((double)i*160/(double)SAMPLE_RATE) * M_PI * 2. ));
        test2[i] = (float) (0.5 * sin( ((double)i*220/(double)SAMPLE_RATE) * M_PI * 2. ));
    }
    //ARR_DBUG(test1);
    */
}

Mixer::Mixer(const Mixer& orig) {
}

Mixer::~Mixer() {
    for(int i = 0; i < input.size(); i++) {
        delete [] input[i].data;
        delete [] input[i].queue;
    }
    input.clear();
    output.clear();
}

void Mixer::startProcess() {
    mutex.lock();
    m_abort = false;
    mutex.unlock();
    
    start();
}

void Mixer::stopProcess() {
    mutex.lock();
    m_abort = true;
    mutex.unlock();
}

void Mixer::run(){
    while(true){
        if (m_abort)
            return;
        
        // NB. It's become impossible to debug anything, while these functions are active! Comment them out for any module debug
        //FetchSound();
        MixSounds();
        OutputSounds();
        msleep(timeout);
    }
}

AddSoundResult Mixer::AddSound(QVector<float>& in, void* caller, bool trunked) {
    if (count >= MAX_INPUTS) return FULL;
    if (in.size() > MAX_VECTOR_SIZE && !trunked) return ERROR;
    
    for(int i = 0; i < count; i++) {
        if (input[i].sender == caller) {
            if ( (input[i].data_size <= input[i].ptr || input[i].force_swap) 
                    && input[i].queue_size > 0) {
                ProcessQueue(input[i]);
            }
            return WAIT; // use Queue instead
        }
    }
    
    if (in.size() > MAX_VECTOR_SIZE) in.resize(MAX_VECTOR_SIZE);
    input[count].sender = caller;
    input[count].force_swap = false;
    input[count].data_size = in.size();
    for(int i = 0; i < input[count].data_size; i++) {
        input[count].data[i] = in[i];
    }
    //input[count].queue.clear();
    input[count].queue_size = 0;
    input[count].ptr = 0;
    //input[count].processing.unlock();
    count++;
    
    //std::cout << " +1 ";
    //std::cout.flush();
    return SUCCESS;
}

AddSoundResult Mixer::QueueSound(QVector<float>& in, void* caller, bool trunked, bool override) {
    if (in.size() > MAX_VECTOR_SIZE && !trunked) return ERROR;
    
    for(int i = 0; i < count; i++) {
        if (input[i].sender == caller) {
            if (input[count].queue_size > 0) {
                if (input[i].data_size <= input[i].ptr || input[i].force_swap) {
                    ProcessQueue(input[i]); // Free (process) queue and attach a new one
                } else if (!override) 
                    return WAIT;
            }
            if (in.size() > MAX_VECTOR_SIZE) in.resize(MAX_VECTOR_SIZE);
            input[count].queue_size = in.size();
            for(int j = 0; j < input[count].queue_size; j++) {
                input[count].queue[j] = in[j];
            }
            return SUCCESS;
        }
    }
    
    // No existing data or queue found; adding as usual
    if (count >= MAX_INPUTS) return FULL;
    return AddSound(in, caller, trunked);
}

AddSoundResult Mixer::ForceSound(QVector<float>& in, void* caller, bool trunked) {
    if (in.size() > MAX_VECTOR_SIZE && !trunked) return ERROR;
    if (in.size() > MAX_VECTOR_SIZE) in.resize(MAX_VECTOR_SIZE);
    
    for(int i = 0; i < count; i++) {
        if (input[i].sender == caller) {
            if (input[i].data_size <= input[i].ptr) {//|| input[i].processing.tryLock()) {
                input[count].data_size = in.size();
                for(int j = 0; j < input[count].data_size; j++) {
                    input[count].data[j] = in[j];
                }
                input[i].ptr = 0;
                input[i].force_swap = false; // if queued something else
                //input[i].processing.unlock();
            } else {
                input[count].queue_size = in.size();
                for(int j = 0; j < input[count].queue_size; j++) {
                    input[count].queue[j] = in[j];
                }
                input[i].force_swap = true;
            }
            return SUCCESS;
        }
    }
    
    // No existing data or queue found; adding as usual
    if (count >= MAX_INPUTS) return FULL;
    return AddSound(in, caller, trunked);
}

void Mixer::ProcessQueue(MixData& data) {
    //data.processing.lock();
    input[count].data_size = input[count].queue_size;
    for(int j = 0; j < input[count].data_size; j++) {
        input[count].data[j] = input[count].queue[j];
    }
    input[count].queue_size = 0;
    data.ptr = 0;
    data.force_swap = false;
    //data.processing.unlock();
}

void Mixer::MixSounds() {
    double G, RMS = 0; // root-mean-square
    
    for (int i = 0; i < AUDIO_BUF_SIZE; i++) {
        output[i] = 0;
    }
    
    for(int i = 0; i < count; i++) {
        int j, k;
        
        //input[i].processing.lock();
        
        for (j = input[i].ptr, k = 0; j < MIN(input[i].ptr + AUDIO_BUF_SIZE, input[i].data_size); j++, k++) {
            output[k] += input[i].data[j];
            // TEST
            //if (j % 1000 == 0 ) std::cout << " j=" << j;
        }
        //j -= input[i].ptr;
        input[i].ptr += j - input[i].ptr;
        //std::cout << " i = " << i << " Ptr = " << input[i].ptr << " Data size = " << input[i].data_size <<"\n";
        //while (j < AUDIO_BUF_SIZE) output[j] += 0;
        if (input[i].data_size <= input[i].ptr) {
            if (input[i].queue_size > 0) {
                ProcessQueue(input[i]);
            } else {
                // no more data
                input[i].sender = NULL;
                input[i].force_swap = false;
                input[i].data_size = 0;
                input[i].queue_size = 0;
                input[i].ptr = 0;
                
                MixData tmp;
                for(j = i; j < count - 1; j++) {
                    tmp.sender = input[j].sender;
                    tmp.data = input[j].data;
                    tmp.data_size = input[j].data_size;
                    tmp.queue = input[j].queue;
                    tmp.queue_size = input[j].queue_size;
                    tmp.ptr = input[j].ptr;
                    //tmp.processing = input[i].processing;
                    tmp.force_swap = input[j].force_swap;
         
                    input.replace(j, input[j+1]);
                    input.replace(j+1, tmp);
                }
                //input[count].processing.unlock();
                count--;
                i--; // to place iterator on next actual element
            }
        } else {
           //input[i].processing.unlock(); 
        }
        
        if (i >= count) break; // dunno why it's not automatic break
        
    }
    //count = 0;
    //std::cout << " +2 ";
    //std::cout.flush();
    //if (input[0].ptr < 3000) ARR_DBUG(output);
    
    for (int i = 0; i < AUDIO_BUF_SIZE; i++) {
        RMS += sq(output[i]);
    }
    RMS /= AUDIO_BUF_SIZE;
    RMS = MAX(sqrt(RMS), 1); // may me empty vector
    //assert(RMS != 0);
    
    // gain calc.
    G = gain / (M_SQRT2 * RMS); //double GainMaster = 0x7fff / (sqrt(2)*RMS);
    for (int i = 0; i < AUDIO_BUF_SIZE; i++) {
        output[i] *= G;
    }
    for (int i = 0; i < AUDIO_BUF_SIZE; i++) {
        if (output[i] > gain) output[i] = gain;
        else if (output[i] < -gain) output[i] = -gain;
    }
}

void Mixer::OutputSounds() {
    std::vector<float> out = std::vector<float>(output.toStdVector());
    audio->SetOutput(out);
}

// TEST - passed
/*
void Mixer::FetchSound() {
    std::vector<float> in;
    QVector<float> out(AUDIO_BUF_SIZE);
    
    in = audio->GetSoundInput_safe();
    for (int i = 0; i < AUDIO_BUF_SIZE; i++) {
        out[i] = in[i];
    }
    
    AddSound(out, this);
    
    
    //TEST - passed
    
    //QueueSound(test1, (void*)0x00000001);
    //std::cout << " +0 ";
    //std::cout.flush();
    //QueueSound(test2, (void*)0x00000001, false, true);
}
/**/