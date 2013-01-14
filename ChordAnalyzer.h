/* 
 * File:   ChordAnalyzer.h
 * Author: astral
 *
 * Created on 2 Ноябрь 2012 г., 19:51
 */

/*
 * Based on "Multiple Fundamental Frequency Estimation by Summing Harmonic Amplitudes" by Anssi Klapuri.
 * Credits to PolyphonicPitchDetection project (https://github.com/tjrantal/PolyphonicPitchDetection)
 * and multi-f0-estimation project (https://github.com/gburlet/multi-f0-estimation)
 */

#ifndef CHORDANALYZER_H
#define	CHORDANALYZER_H

#include "common.h"
#include "AudioIO.h"
#include <math.h>
#include <vector>
#include "kiss_fft/kiss_fftr.h"
#include <QThread>
#include <QMutex>
#include <assert.h>

#define NU 0.33
const float nu_1 = NU-1;
#define GAMMA 0.7

// 46 ms frame
/*
#define ALPHA 27
#define BETA 320
#define D 1.0
*/
// 93 ms frame
#define ALPHA 52
#define BETA 320
#define D 0.89

#define SUB_BANDS 30
#define HARMONICS 20

#define MIN_FREQ 65
#define MAX_FREQ 2100

#define MAX_TONES 7

class ChordAnalyzer : public QThread {
    Q_OBJECT
public:
    ChordAnalyzer(unsigned int n, double sample_rate, AudioIO* audio);
    virtual ~ChordAnalyzer();
    
    void GetTones(std::vector<float>& tones, int& count);
    
    // Thread routine
signals:
    void sendAnalyzerData(float*, int);
public slots:
    void startProcess();
    void stopProcess();
private:
    void run();
private:
     bool m_abort;
     QMutex mutex;  
     
private:
    __inline float Salience(float t_low, float t_up); // s(t)
    __inline float IterativeEstimation (float *t_ret); // algorithm itself to call s(t); returns s, t_ret acts as OUT parameter
    __inline void SpectralWhitening(std::vector<float>& input, std::vector<float>& output); // Hb(k)
    __inline void Yd_cancelation(float t);
    
private:
    AudioIO* audio;
    
    unsigned int n, size;
    unsigned int n_for_single; // this is used to determinate whether use GetInput_safe() or GetExtendedInput_safe()
    double sample_rate;
    std::vector<float> white_input; // Yr
    std::vector<float> Yd;
    std::vector<float> frequence_bands; // indexed array of freq bands (and F0s)
    //std::vector<float> f0_candidates;
    std::vector<float> f0_indexes;
    std::vector<float> Cb; // Center frequencies cb [Hz] of the subbands; cb = 229 * (10^((b+1)/21.4) - 1)
    std::vector<float> Hb; // Traingular responses of Cb-1 .. Cb+1, where Cb -s center
    std::vector<int> Hb_indexes;
    std::vector<float> g;
    
    //FFT variables
    kiss_fftr_cfg   cfgAutocorrTime2FFT, cfgAutocorrFFT2Time;
    kiss_fft_scalar *autocorrTime;
    kiss_fft_cpx   *autocorrFFT;
};

#endif	/* CHORDANALYZER_H */

