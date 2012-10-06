/* 
 * File:   SingleToneAnalyzer.h
 * Author: astral
 *
 * Created on 1 Август 2012 г., 23:36
 */

/* This code was copied frop oTuner, that had beed created based on Tartini project
 * All credit goes to Philip McLeod, Geoff Wyvill, "A SMARTERWAY TO FIND PITCH",
 * University of Otago, 2005
 */

#ifndef SINGLETONEANALYZER_H
#define	SINGLETONEANALYZER_H

#include "Analyzer.h"
#include "AudioIO.h"
#include <math.h>
#include <vector>
#include "kiss_fft/kiss_fftr.h"
#include <QThread>
#include <QMutex>

#define sq(x) (x*x)
//extern double stdAutoCorr(const kiss_fft_scalar *input, float *output, unsigned long const tSize, unsigned long const pBiscN, unsigned long const tK);
static const double dBFloor = -120.0;

// oTuner implimentation, base form C0
// static const char *noteNames[12] = { "C ", "C#", "D ", "D#", "E ", "F ", "F#", "G ", "G#", "A ", "A#", "B " };

// Using pitch from A2 (27.5 Hz)
static const char *noteNames[12] = {"A ", "A#", "B " , "C ", "C#", "D ", "D#", "E ", "F ", "F#", "G ", "G#"};

class SingleToneAnalyzer : public QThread {// : public Analyzer {
    Q_OBJECT
public:
    SingleToneAnalyzer(unsigned int n, double sample_rate, AudioIO* audio);
    virtual ~SingleToneAnalyzer();
    
    /* Main tone analyzer interface.
     * Gets audio input from AudioIO thread.
     * [OUT] freq - determined frequency
     * [OUT] pitch - determined pitch - half-tone steps, where 1 is A2 (27.5 Hz)
     * [OUT] note - determined note
     * Returns true on successful determination
     */
    bool GetTone(double& freq, int& pitch, const char*& note, double& logPower);
    
    /**
    @param input An array of floats to be processed to find the pitch of
    @param logPower The volume is returned in this
    @param freq The freq is returned in this
    */
    //bool find_pitch(kiss_fft_scalar *input, double *freq, double *logPower);
    bool find_pitch(std::vector<float>& input, double& freq, double& logPower);
    
    /** Converts the frequencies freq (in hertz) into their note number on the midi scale
        i.e. the number of semi-tones above C0
        Note: The note's pitch will contain its fractional part
        Reference = http://www.borg.com/~jglatt/tutr/notenum.htm
    @param freq The frequency in Hz
    @return The pitch in fractional part semitones from the midi scale.
    */
    __inline double freq2pitch(double freq)
    {
    #ifdef log2
            return -36.3763165622959152488 + 12.0*log2(freq);
    #else
            // Dunno what oTuner author ment by this magic number, but result is not that I expected
            // return -36.3763165622959152488 + 39.8631371386483481*log10(freq);
            // I'll use pitch scaled from A2 = 27.5 Hz
            return ((log10( freq / 27.5 )) / 0.02508583297199843293447824122704); // that is (log10( freq / 27.5 )) / (log10( 2 ^ 1/12 ))
            
    #endif
    }
     
    const char* noteName(int pitch) { return noteNames[cycle(pitch, 12)]; } // as for pitch = 1 => A

// Thread routine
signals:
    void sendAnalyzerData(bool result, double freq, int pitch, const char* note, double logPower);
public slots:
    void startProcess();
    void stopProcess();
private:
    void run();
private:
     bool m_abort;
     QMutex mutex;    
    
private:
    /** Performs an autocorrelation on the input
    @param input An array of length n, in which the autocorrelation is taken
    @param ouput This should be an array of length k.
        This is the correlation of the signal with itself
        for delays 1 to k (stored in elements 0 to k-1)
    @return The sum of squares of the input. (ie the zero delay correlation)
        Note: Use the init function to set values of n and k before calling this.
    */

    double autocorr(std::vector<float>& input, std::vector<float>& output);
    
    /** The Normalised Square Difference Function.
    @param input. An array of length n, in which the ASDF is taken
    @param ouput. This should be an array of length k
    @return The sum of squares of the input
    */
    //double nsdf(const kiss_fft_scalar *input, float *output);
    //double nsdf(const std::vector<float>& input, std::vector<float>& output);
    double nsdf(std::vector<float>& input, std::vector<float>& output);
    
    /**
        Find the highest maxima between each pair of positive zero crossings.
        Including the highest maxima between the last +ve zero crossing and the end if any.
        Ignoring the first (which is at zero)
        In this diagram the disired maxima are marked with a *

        *             *
        \      *     /\      *     /\
        _\____/\____/__\/\__/\____/__
          \  /  \  /      \/  \  /
           \/    \/            \/

    @param input The array to look for maxima in
    @param len Then length of the input array
    @param maxPositions The resulting maxima positions are pushed back to this vector
          Array of length "len"
    @param NumActualIndicies returns Number of populated entries in maxPositions
    @return The index of the overall maximum
    */
    int findNSDFMaxima(std::vector<float>& input, int len, std::vector<int>& maxPositions);//, unsigned int * NumActualIndicies);
    
    /** 
    @return The index of the first sub maximum.
        This is now scaled from (threshold * overallMax) to 0.
    */
    int findNSDFsubMaximum(std::vector<float>& input, int len, float threshold);
    
    __inline double bound_double(double var, double lowerBound, double upperBound)
    {
        //this way will deal with NAN, setting it to lowerBound
        if(var >= lowerBound) {
            if(var <= upperBound) return var;
            else return upperBound;
        } else return lowerBound;
    }
    
    /** Calculate the x position and the y position of the min/max of a parabola at the same time
    @param y_1, y0 and y1 are the values of the function at xOffset-1, xOffset and xOffset+1
    @param xOffset the x value at which y0 is a function of
    @param x The x result will be put in here
    @param y The y result will be put in here
    */
    __inline void parabolaTurningPoint2(float y_1, float y0, float y1, float xOffset, float *x, float *y)
    {
        float yTop = y_1 - y1;
        float yBottom = y1 + y_1 - 2 * y0;
        if(yBottom != 0.0) {
            *x = xOffset + yTop / (2 * yBottom);
            *y = y0 - ((yTop*yTop) / (8 * yBottom));
        } else {
            *x = xOffset;
            *y = y0;
        }
    }
    
    // round to nearest integers; double and float implementation
    __inline long int lrint (double flt)
    {
        return (int)(floor(flt + 0.5));
    }
    __inline long int lrintf (float flt)
    { 
        return (int)(floor(flt + 0.5));
    }
    
    __inline int toInt(const double x) {
        return lrint(x);
    }
    __inline int toInt(const float x) {
        return lrintf(x);
    }
    
    __inline int cycle(const int a, const int b)
    {
        if(a >= 0) return a % b;
        else return b + ((a+1) % b) - 1;
    }
    
    /* x is between 0 and 1. 1 becomes 0dB and 0 becomes dBFloor (-ve) */
    __inline double linear2dB(double x) { 
        return (x > 0.0) ? bound_double((log10(x) * 20.0), dBFloor, 0.0) : dBFloor;
    }
private:
    AudioIO* audio;
    
    unsigned int n, k, size;
    double sample_rate;
    std::vector<float> autocorr_buf;
    double noiseFloor; //in dB
    
    //FFT variables
    kiss_fftr_cfg   cfgAutocorrTime2FFT, cfgAutocorrFFT2Time;
    kiss_fft_scalar *autocorrTime;
    kiss_fft_cpx    *autocorrFFT;
};

#endif	/* SINGLETONEANALYZER_H */

