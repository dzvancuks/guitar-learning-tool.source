/* 
 * File:   Analyzer.h
 * Author: astral
 *
 * Created on 1 Август 2012 г., 23:28
 */

#ifndef ANALYZER_H
#define	ANALYZER_H

#include <QtCore>

class Analyzer {// : public QThread {
    //Q_OBJECT
public:
    /* Derived classes should use audio vectio input from AudioIO 
     * and has some sort of output, like tone, note or chord. 
     * Retuns true on success, i.e. analyzed data is correct.
     */
    virtual bool GetTone() = 0;
};

#endif	/* ANALYZER_H */

