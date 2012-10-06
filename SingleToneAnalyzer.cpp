/* 
 * File:   SingleToneAnalyzer.cpp
 * Author: astral
 * 
 * Created on 1 Август 2012 г., 23:36
 */

#include "SingleToneAnalyzer.h"

// temporary
#include <iostream>

// n - The size of the incoming buffers (windows)
// sample_rate - The number of samples per second (often 44100)
SingleToneAnalyzer::SingleToneAnalyzer(unsigned int n = BUF_SIZE, double sample_rate = SAMPLE_RATE, AudioIO* audio = NULL) {
    this->audio = (audio != NULL ? audio : new AudioIO());
    
    this->n = n;
    k = n/2;
    size = n+k;
    this->sample_rate = sample_rate;
    noiseFloor = 0.0; //in dB

    autocorr_buf.resize(size); //(sizeof(float) * size);

    //FFT routine
    cfgAutocorrTime2FFT = kiss_fftr_alloc(size, 0, 0, 0); // Time domain -> Freq. domain
    cfgAutocorrFFT2Time = kiss_fftr_alloc(size, 1, 0, 0); // Freq. domain -> Time domain
    autocorrTime = new kiss_fft_scalar[size];
    autocorrFFT  = new kiss_fft_cpx[size/2 + 1];          // Complex structure: ARR[n].r, ARR[n].i; size = sizeof(RT)/2 + 1
    
    // Thread routine
    m_abort = false;
    start(); // TODO comment out. Started by startProcess()
    
    /* Test frequency - PASSED
#define des_freq 164.81
#define freq_len (sample_rate/des_freq)    
    std::vector<float> tmparr;
    double tmpresult, tmplog, pitch;
    bool res;
    
    //tmparr.resize(k);
    //k = tmpsz;
    for(unsigned int i=0; i < n; i++ )
    {
        tmparr.push_back ((float) (0.5 * sin( ((double)i/(double)freq_len) * M_PI * 2. )));
    }
    res = find_pitch(tmparr, &tmpresult, &tmplog);
    pitch = freq2pitch(tmpresult);
    std::cout << "Res = " << res << ", frq = " << tmpresult << ", freq2pitch = " << toInt(pitch) << ", note = " << noteName(toInt(pitch)) << ", log = " << tmplog << "\n";
    */
}

SingleToneAnalyzer::~SingleToneAnalyzer() {
    free(cfgAutocorrTime2FFT);
    free(cfgAutocorrFFT2Time);
    delete[] autocorrTime;
    delete[] autocorrFFT;
    
    mutex.lock();
    m_abort = true;
    mutex.unlock();

    wait();
}

void SingleToneAnalyzer::startProcess() {
    mutex.lock();
    m_abort = false;
    mutex.unlock();
}

void SingleToneAnalyzer::stopProcess() {
    mutex.lock();
    m_abort = true;
    mutex.unlock();
}

void SingleToneAnalyzer::run(){
    double freq;
    int pitch;
    const char* note;
    double logPower;
    bool result;
    
    while(true){
        result = GetTone(freq, pitch, note, logPower);
        
        emit sendAnalyzerData(result, freq, pitch, note, logPower);
        if (m_abort)
            return;
        msleep(10);
    
        //std::cout << "Res = " << result << ", frq = " << freq << ", pitch = " << pitch << ", note = " << note << ", log = " << logPower << "\n";
    }
}



bool SingleToneAnalyzer::GetTone(double& freq, int& pitch, const char*& note, double& logPower){
    bool result;
    std::vector<float> input = audio->GetInput_safe();
    
    result = find_pitch(input, freq, logPower);
    pitch = toInt(freq2pitch(freq));
    note = noteName(pitch);
    return result;
}

bool SingleToneAnalyzer::find_pitch(std::vector<float>& input, double& freq, double& logPower){
        // Process the input samples (bufferSize sample frames) that were read
    double power = nsdf(input, autocorr_buf);
    float x = 0.0f, y = 0.0f;
    int indexOfMax = 1;
    logPower = linear2dB(power/(double)n); //MTB inserted /t->n (similar to main tartini app); otherwise power is not from 0->1, so linear2dB always clips to 0
    if(logPower < noiseFloor) noiseFloor = logPower;

    indexOfMax = findNSDFsubMaximum(autocorr_buf, k, 0.6); // TODO fix koeficients; this part must be expanded to match Tartini algorithm (MyTransforms::calculateAnalysisData)

    //do a parabola fit to find the maximum
    parabolaTurningPoint2(autocorr_buf[indexOfMax-1],
                          autocorr_buf[indexOfMax],
                          autocorr_buf[indexOfMax+1],
                          (float)(indexOfMax + 1), &x, &y);
    freq = (double)(sample_rate) / x;
    y = bound_double(y, -1.0f, 1.0f);

    if (y > 0.9) // if correlation is > 60%
      	if(logPower > noiseFloor + 60) // TODO tapping has low noise floor. Make option-enabled value
            return true;
        else
            return false;
    else 
        return false;
}

double SingleToneAnalyzer::nsdf(std::vector<float>& input, std::vector<float>& output){
    double sumSq = autocorr(input, output); //the sum of squares of the input
    double totalSumSq = sumSq * 2.0;
    unsigned int j;

    //NSDF
    for(j = 0; j < k; j++) {
        totalSumSq  -= sq(input[n-1-j]) + sq(input[j]);//sq(input[n-1-j]/32768.0f) + sq(input[j]/32768.0f);

        if(totalSumSq > 0.0) output[j] *= 2.0 / totalSumSq;
        else output[j] = 0.0;
    }

    return sumSq;
}

double SingleToneAnalyzer::autocorr(std::vector<float>& input, std::vector<float>& output){
    float fsize = float(size);
    unsigned int i;

    for (i = 0; i < n; i++) {
        autocorrTime[i] = input[i];
    }
    for (; i < size; i++) {
        autocorrTime[i] = 0.0f;
    }
    
    //Do a forward FFT
    kiss_fftr(cfgAutocorrTime2FFT, autocorrTime, autocorrFFT);
    
    /*
    calculate the (real*real + imag*imag) for each coefficient
    Note to FFTW: The numbers are packed in half_complex form (refer fftw)
        ie. R[0], R[1], R[2], ... R[size/2], I[(size+1)/2+1], ... I[3], I[2], I[1]
    Note to KISS FFT: The numbers are packed in complex form (refer kiss fftr)
        ie. ARR[0].r, ARR[1].r, ARR[2].r, ... ARR[size/2].r; - real part
            ARR[0].i, ARR[1].i, ARR[2].i, ... ARR[size/2].i; - imag part
    */
    for(i = 1; i < size/2; i++) {
        autocorrFFT[i].r = sq(autocorrFFT[i].r) + sq(autocorrFFT[i].i);
        autocorrFFT[i].i = 0.0f;
    }
    autocorrFFT[0].r = sq(autocorrFFT[0].r);
    autocorrFFT[size/2].r = sq(autocorrFFT[size/2].r);
    
    // Must already be 0
    autocorrFFT[0].i = 0.0f;
    autocorrFFT[size/2].i = 0.0f;
    
    //Do an inverse FFT
    kiss_fftri(cfgAutocorrFFT2Time, autocorrFFT, autocorrTime);

    //extract the wanted elements out, and normalise
    //for(int x=0; x<k; x++)
    //  output[x] = autocorrTime[x+1] / fsize;
    for(i = 0; i < k; i++) {
        output[i] = autocorrTime[i+1] / fsize;
    }
    
    return double(autocorrTime[0]) / double(size);
}

int SingleToneAnalyzer::findNSDFsubMaximum(std::vector<float>& input, int len, float threshold){
    //int s_aIndicies[1024];
    std::vector<int> s_aIndicies;//(len);
    int ret = 0;
    float cutoff;
    //unsigned int NumActualIndicies = 0;
    int overallMaxIndex = findNSDFMaxima(input, len, s_aIndicies);//, &NumActualIndicies);
    
    threshold += (1.0 - threshold) * (1.0 - input[overallMaxIndex]);
    cutoff = input[overallMaxIndex] * threshold;

    for(unsigned int j = 0; j < s_aIndicies.size(); j++) {
        if(input[s_aIndicies[j]] >= cutoff) { ret = s_aIndicies[j]; break; }
    }

    return ret;
}

int SingleToneAnalyzer::findNSDFMaxima(std::vector<float>& input, int len, std::vector<int>& maxPositions) {//, unsigned int * NumActualIndicies){
    int pos = 0;
    int curMaxPos = 0;
    int overallMaxIndex = 0;

    //* NumActualIndicies = 0;

    while(pos < (len-1)/3 && input[pos] > 0.0f) pos++; //find the first negitive zero crossing
    while(pos < len-1 && input[pos] <= 0.0f) pos++; //loop over all the values below zero
    if(pos == 0) pos = 1; // can happen if output[0] is NAN

    while(pos < len-1) {
        if(input[pos] > input[pos-1] && input[pos] >= input[pos+1]) { //a local maxima
            if(curMaxPos == 0) curMaxPos = pos; //the first maxima (between zero crossings)
            else if(input[pos] > input[curMaxPos]) curMaxPos = pos; //a higher maxima (between the zero crossings)
        }
        pos++;
        if(pos < len-1 && input[pos] <= 0.0f) { //a negative zero crossing
            if(curMaxPos > 0) { //if there was a maximum
                maxPositions.push_back(curMaxPos); //add it to the vector of maxima
                //maxPositions[(*NumActualIndicies)++] = curMaxPos;

                if(overallMaxIndex == 0) overallMaxIndex = curMaxPos;
                else if(input[curMaxPos] > input[overallMaxIndex]) overallMaxIndex = curMaxPos;
                curMaxPos = 0; //clear the maximum position, so we start looking for a new ones
            }
            while(pos < len-1 && input[pos] <= 0.0f) pos++; //loop over all the values below zero
        }
    }

    if(curMaxPos > 0) { //if there was a maximum in the last part
        maxPositions.push_back(curMaxPos); //add it to the vector of maxima
        //maxPositions[(*NumActualIndicies)++] = curMaxPos;

        if(overallMaxIndex == 0) overallMaxIndex = curMaxPos;
        else if(input[curMaxPos] > input[overallMaxIndex]) overallMaxIndex = curMaxPos;
        curMaxPos = 0; //clear the maximum position, so we start looking for a new ones
    }
    return overallMaxIndex;
}