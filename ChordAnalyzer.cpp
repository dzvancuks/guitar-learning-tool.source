/* 
 * File:   ChordAnalyzer.cpp
 * Author: astral
 * 
 * Created on 2 Ноябрь 2012 г., 19:51
 */

#include "ChordAnalyzer.h"
#include "Chord.h"

ChordAnalyzer::ChordAnalyzer(unsigned int n, double sample_rate, AudioIO* audio) {
    this->audio = (audio != NULL ? audio : new AudioIO());
    
    assert (BUF_SIZE == 2048 || BUF_SIZE == 4096);
    this->n = 4096;
    //k = this->n; // 0-padding
    size = this->n*2; // + 0-padding
    this->sample_rate = sample_rate;
    //noiseFloor = 0.0; //in dB

    white_input.resize(size/2);
    Yd.resize(size/2);
    Yd.insert(Yd.begin(), size/2, 0);
    
    Cb.resize(SUB_BANDS+2); // as for 0 => b=1-1 and 31 => b=30+1
    for (int i = 0; i <= SUB_BANDS+1; i++) { // 1..30, but subband b has a triangular power response Hb(k) that extends from cb-1 to cb+1 and is zero elsewhere
        Cb[i] = 229 * (powf(10, (i / 21.4) ) - 1);
    }
    
    frequence_bands.resize(size/2);
    for (unsigned i = 0; i < size/2; i++) {
        frequence_bands[i] = (float)i * (sample_rate/size);
    }
    
    int low, high, canditate_size;
    low = high = canditate_size = 0;
    while (frequence_bands[low] <= MIN_FREQ) { low++; }
    high = low;
    while (frequence_bands[high] <= MAX_FREQ) { high++; }
    canditate_size = high - low + 1;
    
    //f0_candidates.resize(canditate_size); // unused: freq taken by frequence_bands[f0_indexes[i]]
    f0_indexes.resize(canditate_size);
    
    for (int i = 0; i < canditate_size; i++) {
        //f0_candidates[i] = frequence_bands[i+low];
        f0_indexes[i] = i+low;
    }
    
    g.resize(HARMONICS);
  
    //FFT routine
    cfgAutocorrTime2FFT = kiss_fftr_alloc(size, 0, 0, 0); // Time domain -> Freq. domain
    cfgAutocorrFFT2Time = kiss_fftr_alloc(size, 1, 0, 0); // Freq. domain -> Time domain
    autocorrTime = new kiss_fft_scalar[size];
    autocorrFFT  = new kiss_fft_cpx[size/2];          // Complex structure: ARR[n].r, ARR[n].i
    for (unsigned int i = 0; i < size; i++) {
        autocorrTime[i] = 0;
        //autocorrTime[i].i = 0;
    }
    for (unsigned int i = 0; i < size/2; i++) {
        autocorrFFT[i].r = 0;
        autocorrFFT[i].i = 0;
    }
    
    // Thread routine
    //startProcess();// started externally
    
    // remove warning
    Q_UNUSED(AboutText);
}

ChordAnalyzer::~ChordAnalyzer() {
    free(cfgAutocorrTime2FFT);
    free(cfgAutocorrFFT2Time);
    delete[] autocorrTime;
    delete[] autocorrFFT;
    
    mutex.lock();
    m_abort = true;
    mutex.unlock();

    wait();
}

void ChordAnalyzer::startProcess() {
    mutex.lock();
    m_abort = false;
    mutex.unlock();
    
    start();
}

void ChordAnalyzer::stopProcess() {
    mutex.lock();
    m_abort = true;
    mutex.unlock();
}

void ChordAnalyzer::run(){
    std::vector<float> tones;
    static float tcopy[MAX_TONES];
    int count;
    
    while(true){
        if (m_abort)
            return;
        
        GetTones(tones, count);
        for (unsigned i = 0; i < tones.size() || i < MAX_TONES; i++) {
            tcopy[i] = tones[i];
        }
        emit sendAnalyzerData(tcopy, MIN(count, MAX_TONES));
        msleep(10);
    
        //std::cout << "Res = " << result << ", frq = " << freq << ", pitch = " << pitch << ", note = " << note << ", log = " << logPower << "\n";
    }
}

void ChordAnalyzer::GetTones(std::vector<float>& tones, int& count){
    int S = 0, S_prev = -1, j=0;
    float s_sum = 0;
    std::vector<float> input = audio->GetExtendedInput_safe();
    
/*  // TEST // Somewhat passed, but VERY buggy!
#define des_freq1 164.81
#define des_freq2 880
#define des_freq3 82.4
#define des_freq4 325
    std::vector<float> input;
    
    input.resize(size/2);
    for(unsigned int i=0; i < size/2; i++ )
    {
        input[i] = (float) (0.25 * sin( ((double)i*des_freq1/(double)sample_rate) * M_PI * 2. ));
        input[i] += (float) (0.25 * sin( ((double)i*des_freq2/(double)sample_rate) * M_PI * 2. ));
        input[i] += (float) (0.25 * sin( ((double)i*des_freq3/(double)sample_rate) * M_PI * 2. ));
        input[i] += (float) (0.25 * sin( ((double)i*des_freq4/(double)sample_rate) * M_PI * 2. ));
    }
    //ARR_DBUG(input);
*/    
    SpectralWhitening(input, white_input);
    Yd.assign(size/2, 0);
    tones.clear();

    float s, t;
    while (S > S_prev) {
        j++;
        S_prev = S;
        
        s = IterativeEstimation(&t);
        Yd_cancelation(t);
        tones.push_back(sample_rate/t);
        
        s_sum += s;
        S = s_sum/powf(j, GAMMA);
    }
    // dispose last round data, as it is used only to determinate S decrease
    //tones.pop_back(); with test data 164.81, 880 and 325, last F0 was found in latest iteration
    count = j;//-1;
    
    // TEST
    /*
    std::cout << "Count = " << j;
    for (int i = 0; i < j; i++) {
         std::cout << " " << tones[i];
    }
    std::cout << "\n";
    /**/
}

void ChordAnalyzer::SpectralWhitening(std::vector<float>& input, std::vector<float>& output) {
    unsigned i, j;
    std::vector<float> gamma_b;
    
    for (i = 0; i < size/2; i++) { // Hanning window
        autocorrTime[i] = input[i] * (0.42 - 0.5 * cos(2.0*M_PI*(float)i / (float)(size/2)) + 0.08*cos(4.0*M_PI*(float)i / (float)(size/2)) );
    }
    // zero padded during init; every whitening is affected only Hann window above (size/2)
    //ARR_DBUG(autocorrTime);
    
    //Do a forward FFT
    kiss_fftr(cfgAutocorrTime2FFT, autocorrTime, autocorrFFT);
    //ARR_DBUG(autocorrFFT);
    for (i = 0; i < size/2; i++) { // zero pad
        white_input[i] = KISS_FFT_ABS(autocorrFFT[i]);
    }
    //ARR_DBUG(white_input);
    
    gamma_b.resize(SUB_BANDS+2); // 1..30 + extra [0]=0 and [31]=1 for line interpolation
    gamma_b[0] = 0;
    gamma_b[SUB_BANDS+1] = 0;
    float sigma;
    for (i = 1; i <= SUB_BANDS; i++) { // Use OpenCL in future!
        Hb.clear();
        Hb_indexes.clear();
        
        float range = Cb[i+1] - Cb[i-1];
        j = 0;
        while (frequence_bands[j] < Cb[i-1]) { j++; }
        while (frequence_bands[j] <= Cb[i+1]) {
            Hb_indexes.push_back(j);
            Hb.push_back(1 - (Cb[i] - frequence_bands[j]) / range);
            j++;
        }
        
        sigma = 0;
        for (j = 0; j < Hb.size(); j++) {
            sigma += Hb[j] * sq(white_input[Hb_indexes[j]]);

        }
        sigma = sqrtf(sigma / size);
        
        gamma_b[i] = powf(sigma, nu_1);
    }
    //ARR_DBUG(gamma_b);
    
    i = 0;
    j = 1;
    int tmp; // used to determinate steps between 2 Cb
    float koef, step, range; // koef: The coefficients gamma_b are linearly interpolated between the center frequencies cb to obtain compression coefficients gamma(k) for all frequency bins k.
    koef = 0;         // ... only, it is interpolated during runtime, instead of use of another array
    
    tmp = 0;
    while(frequence_bands[tmp++] < Cb[j]);
    range = (float)(tmp-1);
    
    step = gamma_b[j]/range; // y=kx+b; b=0 k=tg()
    while (i < size/2) {
        if (frequence_bands[i] >= Cb[j]) {
            if (j == 31) break; // out of Cb bins
            j++;
            while(frequence_bands[tmp++] < Cb[j]);
            range = (float)(tmp - i - 1);
            step = (gamma_b[j]-gamma_b[j-1])/range;
        }
        white_input[i] *= koef;
        koef += step;
        i++;
    }
    
    //ARR_DBUG(white_input);
}

float ChordAnalyzer::Salience(float t_low, float t_high) {
    float s = 0;
    float t = (t_low + t_high)/2;
    float delta_t = t_high - t_low;
    
    //int harmonics_num = floor(t/2); // same as (sample_rate(44100)/2)/F0
    //std::vector<float> harmonics;
    //harmonics.resize(harmonics_num);
    
    //std::vector<float> g;
    //g.resize(HARMONICS);
    float bin_t_low = sample_rate/t_low;
    float bin_t_high = sample_rate/t_high;
    for (int i = 0; i < HARMONICS; i++) {
        //g[i] = (sample_rate/t_low + ALPHA)/((i+1)*sample_rate/t_high + BETA);
        g[i] = (bin_t_low + ALPHA)/((i+1)*bin_t_high + BETA);
    }
    
    unsigned int vicinity_low = floorf(((float)size)/(t + delta_t/2) + 0.5);
    unsigned int vicinity_high = floorf(((float)size)/(t - delta_t/2) + 0.5);
    
    // max(k C k(t,m)), k(t,m) = [<mK/(t+Dt/2)>, ..., <mK/(t-Dt/2)>]
    for (int m = 1; m <= HARMONICS; m++) {
            if (m*vicinity_low > f0_indexes.back()) break; // no whitening applied after 2100Hz
            int harmonic_low = m*vicinity_low;
            int harmonic_high = MIN(m*vicinity_high, f0_indexes.back());//size/2);
            
            //int harmonics_bin = 0;
            float harmonic_amp = 0;
            for (int j = harmonic_low; j <= harmonic_high; j++) {
                if (white_input[j] > harmonic_amp) {
                    //harmonics_bin = j;
                    harmonic_amp = white_input[j];
                }
            }
            s += g[m-1]*harmonic_amp;
    }
    
    // Dirty hack to avoid lower harmonics and find F0
#define SALIENCE_CAP 10
    if (s > SALIENCE_CAP && vicinity_high - vicinity_low <= 1) { // if we are about ready to determinate exact F0
        float first_harmonic_amp = 0;
        float max_harmonic_amp = 0;
        
        for (unsigned int j = vicinity_low; j <= vicinity_high; j++) { // try to compare F0 in this cycle ...
            if (white_input[j] > first_harmonic_amp) {
                first_harmonic_amp = white_input[j];
            }
        }
        for (int m = 2; m <= HARMONICS; m++) {
            if (m*vicinity_low > f0_indexes.back()) break;
            int harmonic_low = m*vicinity_low;
            int harmonic_high = MIN(m*vicinity_high, f0_indexes.back());//size/2);
            
            for (int j = harmonic_low; j <= harmonic_high; j++) { // ... with others few ...
                if (white_input[j] > max_harmonic_amp) {
                    max_harmonic_amp = white_input[j];
                }
            }
        }
        // ... and if it is less than other maximas by 50% ...
        if (first_harmonic_amp < max_harmonic_amp && first_harmonic_amp/max_harmonic_amp < 0.5) {
            s = 0; // ... discard it from further use
        }
    }
/**/
    return s;
}

float ChordAnalyzer::IterativeEstimation(float *t_ret) {
    unsigned Q = 0;
    unsigned q_best = 0;
    //unsigned qb_Q_arr[2]; // array that contain only 2 indexes: q_best and new Q
    unsigned q; // iterator [q_best, Q]
    static const float t_min = floorf(sample_rate/frequence_bands[f0_indexes.back()] + 0.5);
    static const float t_max = floorf(sample_rate/frequence_bands[f0_indexes[0]] + 0.5);
    static const float t_prec = 0.5;
    std::vector<float> t_low;
    std::vector<float> t_high;
    std::vector<float> s_max;
    //float s;
    
    t_low.push_back(t_min);
    t_high.push_back(t_max);
    s_max.push_back(0); // just to be able to access to s_max[q_best] on 1-st iteration
    
    while (t_high[q_best] - t_low[q_best] > t_prec) {
        // Split the best block and compute new limits
        Q++;
        t_low.push_back((t_high[q_best] + t_low[q_best])/2);
        t_high.push_back(t_high[q_best]);
        t_high[q_best] = t_low[Q];
        
        // Compute new saliences for the two block-halves
        s_max[q_best] = Salience(t_low[q_best], t_high[q_best]);
        s_max.push_back(Salience(t_low[Q], t_high[Q]));
        /*
        qb_Q_arr[0] = q_best;
        qb_Q_arr[1] = Q;
        for (int i = 0; i < 2; i++) {
            q = qb_Q_arr[i];
            s = Salience(t_low[q], t_high[q]);
            
            if (q == q_best && s_max.size() - q > 0) { // existing element
                s_max[q] = s;
            } else { // if (s_max.size() - q == 0) { // new element
                s_max.push_back(s);
            }
        }
        */
        
        q_best = 0;
        for (q = 1; q <= Q; q++) {
            if (s_max[q] > s_max[q_best]) {
                q_best = q;
            }
        }
    }
    
    // estimated fundamental period of the frame
    *t_ret = (t_low[q_best] + t_high[q_best])/2;
    //*t_ret_low = t_low[q_best];
    //*t_ret_high = t_high[q_best];
    return Salience(t_low[q_best], t_high[q_best]);
}

void ChordAnalyzer::Yd_cancelation(float t) {
    //int harmonics_num = floor(t/2);
    int vicinity = floorf(((float)size)/t + 0.5);
    
    // max(k C k(t,m)), k(t,m) = [<mK/(t+Dt/2)>, ..., <mK/(t-Dt/2)>]
    /*
    int bin = 0;
    float amp = 0;
    for (int m = 1; m <= HARMONICS; m++) {
        if (white_input[m*vicinity] > amp) {
            bin = m*vicinity;
            amp = white_input[bin];
        }
    }
    */
    
    //float t_low = size/(bin+1);
    //float t_high = size/(bin-1);
    
    //std::vector<float> g;
    //g.resize(HARMONICS);
    float bin_t_low = sample_rate/t;
    float bin_t_high = sample_rate/t;
    for (int i = 0; i < HARMONICS; i++) {
        //g[i] = (sample_rate/t_low + ALPHA)/((i+1)*sample_rate/t_high + BETA);
        g[i] = (bin_t_low + ALPHA)/((i+1)*bin_t_high + BETA);
    }
    //float g = (sample_rate/t_low + ALPHA)/(sample_rate/t_high + BETA);
    for (int i = 0; i < HARMONICS; i++) {
        if (i*vicinity > f0_indexes.back()) break; // no whitening applied after 2100Hz
        for (int j = -2; j <= 2; j++) {
            Yd[i*vicinity + j] += g[i] * white_input[i*vicinity + j];
        }
    }
    //ARR_DBUG(Yd);
    for (unsigned int i = 0; i < white_input.size(); i++) {
        white_input[i] = MAX(white_input[i] - D*Yd[i], 0);
    }
    //ARR_DBUG(white_input);
}