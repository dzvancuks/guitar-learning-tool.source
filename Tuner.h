/* 
 * File:   Tuner.h
 * Author: astral
 *
 * Created on 11 Июль 2012 г., 17:41
 */

#ifndef _TUNER_H
#define	_TUNER_H

#include "ui_Tuner.h"
#include "AudioIO.h"
#include "SingleToneAnalyzer.h"
#include <QString>
#include <vector>

enum InstrumentTypesEnumerator {SixStringE, SixStringD};
typedef struct {
    enum InstrumentTypesEnumerator type;
    const char* name;
    int freq_count; // actual data size of [frequences]
    double frequences[12]; // 12-string guitar = maximum, as I know.
} InstrumentType_t;
static const InstrumentType_t InstrumentTypes[] = {
    {SixStringE, "6-string E", 6, {329.63, 246.94, 196.00, 146.83, 110.00, 82.41, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}},
    {SixStringE, "6-string drop D", 6, {329.63, 246.94, 196.00, 146.83, 110.00, 73.42, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}}
};

class Tuner : public QDialog {
    Q_OBJECT
public:
    Tuner();
    Tuner(AudioIO* audio, SingleToneAnalyzer* analyzer);
    virtual ~Tuner();
    
public slots:
    void Tune(bool result, double freq, int pitch, const char* note, double logPower);      // Show tune data itself
    
private:
    void TunerInit(); // private use - creates widget
    
    Ui::Tuner widget;
    AudioIO* audio;
    SingleToneAnalyzer* sAna;
};

#endif	/* _TUNER_H */
