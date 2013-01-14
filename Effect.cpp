/* 
 * File:   Effect.cpp
 * Author: astral
 * 
 * Created on 25 Декабрь 2012 г., 19:44
 */

#include "Effect.h"
#include "AudioIO.h"

Effect::Effect(QWidget* parent, QGridLayout *layout, QString name) : QWidget(parent) {
    if (!name.isEmpty()) {
        QFont font;
        font.setPointSize(10);
        font.setWeight(75);

        QString s = "Effect" % name % "Title";
        title = new QLabel(parent);
        title->setObjectName(s);
        title->setEnabled(true);
        //title->setGeometry(QRect(0, 0, FX_VISUAL_X, TITLE_Y));
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);
        title->setText(QApplication::translate("EffectPump", name.toAscii(), 0, QApplication::UnicodeUTF8));
    }
    
    /*
    close = new QPushButton(parent);
    if (!name.isEmpty()) {
        QString s = "Effect" % name % "Close";
        close->setObjectName(s);
    } else {
        close->setObjectName(QString::fromUtf8("EffectClose"));
    }
    //close->setGeometry(QRect(FX_VISUAL_X - 20, TITLE_Y + 1, 20, 20));
    close->setText(QApplication::translate("EffectPump", "X", 0, QApplication::UnicodeUTF8));
    */

    if (layout) {
        this->layout = layout;
        this->layout->addWidget(title, 0, 0, 2, 0);
        //this->layout->setColumnMinimumWidth(0, round(FX_VISUAL_X*0.85));
        //this->layout->addWidget(close, 1, 0, 2, 0);
    } else {
        this->layout = NULL;
    }
}

Effect::~Effect() {
    while (layout->count()) {
        QWidget *w = layout->itemAt(0)->widget();
        layout->removeItem(layout->itemAt(0));
        delete w;
    }
}

void Effect::LC_filter(QVector<float> *sound, int filter_no, double freq, struct filter_data *pp) {
    double R, L, C, dt_div_L, dt_div_C;
    double du, d2i; //, di
    int t;

    L = 200e-3; /* like original crybaby wahwah, hehehe */
    C = 1.0/(4.0*pow(M_PI*freq, 2.0)*L);
    R = 500.0;

    dt_div_C = 1.0/(C*SAMPLE_RATE);
    dt_div_L = 1.0/(L*SAMPLE_RATE);

    for(t = 0; t < sound->size(); t++) {
        du = (double)sound->at(t) - pp->last_sample[filter_no][0];
        pp->last_sample[filter_no][0] = (double)sound->at(t);

        d2i = dt_div_L * (du-pp->i[filter_no][0]*dt_div_C - R*pp->di[filter_no][0]);
        pp->di[filter_no][0] += d2i;
        pp->i[filter_no][0] += pp->di[filter_no][0];

        //    *sound=(int)(pp->i[filter_no][0]*pp->amplify);
        (*sound)[t] = (float)(pp->i[filter_no][0] * 500.0);
    }
}

void Effect::RC_setup(int max, double amplify, struct filter_data *pp) {
    int c, d; 

    pp->max = max;
    pp->amplify = amplify;

    for(c = 0; c < max; c++) { // or just use memset()
        for(d = 0; d < 2; d++) {
                pp->i[c][d] = pp->di[c][d] = pp->last_sample[c][d] = 0;
        }
    }
}

void Effect::RC_set_freq(double f, struct filter_data *pp) {
    pp->R = 1000.0;
    pp->C =  1.0/(2*M_PI * f * pp->R);
    pp->invR = 1.0/pp->R;
    pp->dt_div_C = (1.0/SAMPLE_RATE)/pp->C;
}

void Effect::RC_filter(QVector<float> *sound, int mode, int filter_no, struct filter_data *pp) {
    double du, di;
    int t;

    for(t = 0; t < sound->size(); t++) {
        du = (double)sound->at(t) - pp->last_sample[filter_no][mode];
        pp->last_sample[filter_no][mode] = (double)sound->at(t);

        di = pp->invR * (du - pp->i[filter_no][mode]*pp->dt_div_C);
        pp->i[filter_no][mode] += di;
        if(mode == HIGHPASS) {
            (*sound)[t] = (float)( (pp->i[filter_no][mode] * pp->R) * pp->amplify);
        } else {
            (*sound)[t] = (float)( ((double)sound->at(t) - pp->i[filter_no][mode] * pp->R) * pp->amplify );
        }
    }
}

void Effect::RC_bandpass(QVector<float> *sound, struct filter_data *pp) {
    int a;

    for(a = 0; a < pp->max; a++) {
        RC_filter(sound, HIGHPASS, a, pp);
        RC_filter(sound, LOWPASS, a, pp);
    }
}

void Effect::RC_highpass(QVector<float> *sound, struct filter_data *pp) {
    int a;

    for(a = 0; a < pp->max; a++)
        RC_filter(sound, HIGHPASS, a, pp);
}

void Effect::RC_lowpass(QVector<float> *sound, struct filter_data *pp) {
    int a;

    for(a = 0; a < pp->max; a++)
        RC_filter(sound, LOWPASS, a, pp);
}
