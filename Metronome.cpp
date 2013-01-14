/* 
 * File:   Metronome.cpp
 * Author: astral
 * 
 * Created on 16 Декабрь 2012 г., 21:26
 */

#include "Metronome.h"
#include "LoadStore.h"

Metronome::Metronome(Mixer* mixer) {
    this->mixer = mixer;
    
    output_data.resize(AUDIO_BUF_SIZE);
    input_data.clear();
    output_data_all.clear();
    pos = 0;
    
    //output_format.setSampleSize(16); // float
    //output_format.setSampleRate(44100);
    //output_format.setChannelCount(1);
    //output_format.setCodec("audio/pcm");
    //output_format.setByteOrder(QAudioFormat::LittleEndian);
    //output_format.setSampleType(QAudioFormat::UnSignedInt);
    output_format.channel_count = 1;
    output_format.sample_rate = SAMPLE_RATE;
    output_format.data_size = 0; // unused
    output_format.sample_size = 0; // unused
    
    //GenerateSound();
    //InterpolateInput();
    SetSoundType(":/sounds/metronome-click.wav"); // default sound
    
    interval = 1000; // resets after SetInterval() and Sync()
    ignore_timeout = false;
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(OutputSound()));
    timer.setSingleShot(true);
    time.start();
    
    // Test Passed
    //Start();
}

Metronome::Metronome(const Metronome& orig) {
}

Metronome::~Metronome() {
    //f.close();
    //timer.stop();
}

/* // use SIGNAL(timeout()) instead
void Metronome::startProcess() {
    mutex.lock();
    m_abort = false;
    mutex.unlock();
    
    start();
}

void Metronome::stopProcess() {
    mutex.lock();
    m_abort = true;
    mutex.unlock();
}

void Metronome::run(){
    while(true){
        if (m_abort)
            return;
        
        time.restart();
        OutputSound();
        
        msleep(timer);
    }
}
*/

void Metronome::SetSoundType(QString type) {
    Stop();
    f.setFileName(type);
    GenerateSound();
    InterpolateInput();
    //Start();
}

void Metronome::Sync() {
    Stop();
    time.restart();
    ignore_timeout = true;
    pos = 0;
    OutputSound();
    timer.start(interval); // reset timer, despite of OutputSound() routine;
}

void Metronome::GenerateSound() {
    if(f.open(QIODevice::ReadOnly)) {
        //char tmp_buf[4];
        int tmp_int;
        
        input_data.clear();
        output_data_all.clear();
        
        // Header
        memset(&input_format, 0, sizeof(input_format));
        
        input_format.data_size = f.size() - 44;
        if (input_format.data_size <= 0) {
            // TODO raise warning
            f.close();
            return;
        }
        
        tmp_int = 0;
        f.seek(22);
        f.read((char*)&tmp_int, 2);
        //f.read(tmp_buf, 2);
        //tmp_int = tmp_buf[1] << 8 | tmp_buf[0];
        input_format.channel_count = tmp_int;
        
        tmp_int = 0;
        f.seek(24);
        f.read((char*)&tmp_int, 4);
        //f.read(tmp_buf, 4);
        //tmp_int = (tmp_buf[3] << 24) | (tmp_buf[2] << 16) | (tmp_buf[1] << 8);// | tmp_buf[0];
        input_format.sample_rate = tmp_int;
        
        tmp_int = 0;
        f.seek(34);
        f.read((char*)&tmp_int, 2);
        //f.read(tmp_buf, 2);
        //tmp_int = tmp_buf[1] << 8 | tmp_buf[0];
        input_format.sample_size = tmp_int / 8;
        
        input_format.data_size /= input_format.sample_size;
        input_format.data_size /= input_format.channel_count;
        
        // Data
        f.seek(44);
        input_data = f.readAll();
        f.close();
    }
}

void Metronome::InterpolateInput() {
    // TMP - to delete and create proper interpolation
    
    QDataStream input_stream(input_data);
    //ARR_DBUG(input_data);
    output_data_all.resize(input_format.data_size); // will be  ceil(input_format.data_size * 44100/input_format.sample_rate)
    
    if (input_format.sample_size == 1) {
        qint8 in;
        
        for (int i = 0; i < input_format.data_size; i++) {
            input_stream >> in;
            output_data_all[i] = (float)in/(float)std::numeric_limits<qint8>::max();
            if (input_format.channel_count == 2) input_stream >> in; // skip other channel
        }
    } else if (input_format.sample_size == 2) {
        quint8 in1, in2;
        qint16 in;
        
        for (int i = 0; i < input_format.data_size; i++) {
            input_stream >> in1; input_stream >> in2;
            in = in2 << 8 | in1;
            //input_stream >> in;
            output_data_all[i] = (float)in/(float)std::numeric_limits<qint16>::max();
            if (input_format.channel_count == 2) input_stream >> in; // skip other channel
        }
    } else {
        //TODO error!!
    }
}

void Metronome::OutputSound() {
    //if (pos >= output_data_all.size()) return;
    
    timer.start(interval - (ignore_timeout ? (time.restart() - interval) : 0) );
    ignore_timeout = false; // one shot at sync() only
    
    int offset = MIN(MAX_VECTOR_SIZE, output_data_all.size() - pos);
    int i;
    for (i = 0; i < offset; i++) {
        output_data[i] = output_data_all[pos + i];
    }
    while(i < AUDIO_BUF_SIZE) { // zero padding
        output_data[i] = 0;
        i++;
    }
    //pos += offset;
    
    AddSoundResult result;
    result = mixer->AddSound(output_data, this);
    if (( result = mixer->AddSound(output_data, this) ) == ERROR) {
        // TODO alert or smth
    } else {
        while (result != SUCCESS) {
            // WAIT - TODO (thread sleep or ??)
            result = mixer->QueueSound(output_data, this);
        }
    }
}
