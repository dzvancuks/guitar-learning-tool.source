/* 
 * File:   common.h
 * Author: astral
 *
 * Created on 24 Октябрь 2012 г., 18:19
 */

#ifndef COMMON_H
#define	COMMON_H

static const char* AboutText = ""
    "\"Guitar Learning Tool\" itself is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.\n\n"
    "\"Guitar Learning Tool\" itself is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n\n"
    "Authors are not responsible for any contents that are used as 'lesson materials'. It's your responsibility to create and distribute these materials FREE of charge or by SELLING them. Authors are not responsible for any intellectual property damage.\n\n"
    "Powered by PortAudio Cross-platform Audio I/O system.\n\n"
    "Windows version uses ASIO Interface Technology by Steinberg Media Technologies GmbH.";

#define MAX(a,b) ((a > b) ? a : b)
#define MIN(a,b) ((a < b) ? a : b)
#define sq(x) ((x)*(x))
#define KISS_FFT_ABS_P2(a) (sq(a.r) + sq(a.i))
#define KISS_FFT_ABS(a) (sqrtf(KISS_FFT_ABS_P2(a)))

/*
#include <vector>
#include "QVector"
#include <QFile>
#include <QTextStream>
#include "kiss_fft/kiss_fftr.h"
static void ARR_DBUG1(float *a, int sz) {//kiss_fft_cpx* a){//std::vector<float>& a) {
    QFile file("DEBUG1.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);         
    for(unsigned iter = 0; iter < sz; iter++)
        out << a[iter] << "\n";
    file.close();
}
static void ARR_DBUG2(float *a, int sz) {//kiss_fft_cpx* a){//std::vector<float>& a) {
    QFile file("DEBUG2.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);         
    for(unsigned iter = 0; iter < sz; iter++)
        out << a[iter] << "\n";
    file.close();
}
**/
#endif	/* COMMON_H */

