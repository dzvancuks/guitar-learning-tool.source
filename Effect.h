/* 
 * File:   Effect.h
 * Author: astral
 *
 * Created on 25 Декабрь 2012 г., 19:44
 */

/*
 * All credits to Marin Vlah and its GUITAR FX PROCESSOR project: http://fly.srk.fer.hr/~mvlah/fx_processor.html
 */

#ifndef EFFECT_H
#define	EFFECT_H

#include <QtGui/QtGui>
#include "qvector.h"
#include <math.h>
#include <assert.h>

#define FX_VISUAL_X (70)
#define FX_VISUAL_Y (100)
#define TITLE_Y (16) // used only for Effects titles; avalable area = FX_VISUAL_Y - TITLE_Y => 74 px

#define MAX_FILTERS 10
#define HIGHPASS 0
#define LOWPASS 1

struct filter_data {
    double i[MAX_FILTERS][2], last_sample[MAX_FILTERS][2];
    int max;
    double amplify, R, C, invR, dt_div_C;
    double di[MAX_FILTERS][2];
};

class Effect : public QWidget {
    Q_OBJECT
public:
    Effect(QWidget *parent = 0, QGridLayout *layout = 0, QString name = QString::QString(""));
    //Effect(const Effect& orig);
    virtual ~Effect();
    
protected: // all are abstracts
    //void mouseMoveEvent(QMouseEvent *event);
    //void mousePressEvent(QMouseEvent *event);
    //void paintEvent(QPaintEvent *event);
    
    static void LC_filter(QVector<float> *, int, double, struct filter_data *);
    static void RC_setup(int, double, struct filter_data *);
    static void RC_set_freq(double, struct filter_data *);
    static void RC_filter(QVector<float> *, int, int, struct filter_data *);
    static void RC_bandpass(QVector<float> *, struct filter_data *);
    static void RC_highpass(QVector<float> *, struct filter_data *);
    static void RC_lowpass(QVector<float> *, struct filter_data *);
    
signals:
    void Ready();
public slots:
    virtual void Process(QVector<float> *input) {}
protected:
    QVector<float> *v;

public: // at least button must be accessible to connect signal
    QGridLayout *layout;
    QLabel *title;
    //QPushButton *close; // not working with grig layout?? Something overlaps it
    //QCheckBox *close;
};

#endif	/* EFFECT_H */

