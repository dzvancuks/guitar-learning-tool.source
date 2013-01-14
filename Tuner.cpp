/*
 * File:   Tuner.cpp
 * Author: astral
 *
 * Created on 11 Июль 2012 г., 17:41
 */

#include "Tuner.h"
#include "Note.h"

Tuner::Tuner() {
    audio = new AudioIO();
    sAna = new SingleToneAnalyzer(BUF_SIZE, SAMPLE_RATE, audio);
    
    TunerInit();
}

Tuner::Tuner(AudioIO* audio, SingleToneAnalyzer* analyzer) {
    this->audio = audio;
    this->sAna = analyzer;
    
    TunerInit();
}

Tuner::~Tuner() {
    sAna->stopProcess();
}

void Tuner::closeEvent(QCloseEvent *event) {
    emit TunerClosed();
    event->accept();
}

void Tuner::TunerInit(){
    unsigned int i;
    
    widget.setupUi(this);
    for (i = 0; i < (sizeof(InstrumentTypes)/sizeof(InstrumentType_t)); i++) {
        widget.TunerGuitarMenu->addItem(QString(InstrumentTypes[i].name));
    }
    SetStrings();
    assert (connect(widget.TunerGuitarMenu, SIGNAL(currentIndexChanged(int)), this, SLOT(SetStrings())) );
    
    QFont font;
    font.setPointSize(10);
    font.setWeight(75);
        
    pointer = new QGraphicsLineItem(0, 0, 0, 0);
    name = new QGraphicsTextItem("");
    name->setFont(font);
    
    scene = new QGraphicsScene(this);
    widget.TunerVisual->setScene(scene);
    widget.TunerVisual->setRenderHint(QPainter::Antialiasing);
    widget.TunerVisual->setAlignment(Qt::AlignLeft);
    scene->setSceneRect(0, 0, 235, 190); // TODO remove hardcoding
    
    QGraphicsEllipseItem *sector = new QGraphicsEllipseItem();//scene);
    scene->addItem(sector);
    //sector->setPos(scene->width()/2, scene->height());
    sector->setRect(-45, 20, scene->width() + 90, 2 * scene->height() - 20);
    sector->setStartAngle(45 * 16);
    sector->setSpanAngle(90 * 16);
    
    scene->addItem(name);
    name->setPos(scene->width()/2 - 10, 0);
    
    QGraphicsTextItem *b = new QGraphicsTextItem("b");
    QGraphicsTextItem *sh = new QGraphicsTextItem("#");
    scene->addItem(b);
    scene->addItem(sh);
    b->setPos(0, 40); // TODO formula based pos calculations
    sh->setPos(scene->width() - 10, 40);
    
    scene->addItem(pointer);
    pointer->setLine(scene->width()/2, scene->height()+10, scene->width()/2, 30);
    pointer->setTransformOriginPoint(scene->width()/2, scene->height()+10);
    
    QPushButton *button;
    if (widget.gridLayout->count() > 2 && 
        ( button = dynamic_cast<QPushButton*>(widget.gridLayout->itemAt(1)->widget()) )) {
        button->setDefault(true);
        SetCurrString();
    }
    
    connect(sAna, SIGNAL(sendAnalyzerData(bool, double, int, const char*, double)), this, SLOT(Tune(bool, double, int, const char*, double)));
    connect(widget.TunerDone, SIGNAL(clicked()), sAna, SLOT(stopProcess()));
    sAna->startProcess();
}

void Tuner::SetStrings() {
    int item = widget.TunerGuitarMenu->currentIndex();
    int count = 0;
    
    while (count < MAX_TUNE_FREQ && InstrumentTypes[item].frequences[count++]);
    count--;
    
    for (int i = 0; i < widget.gridLayout->count(); i++) {
        QPushButton *button;
        if (( button = dynamic_cast<QPushButton*>(widget.gridLayout->itemAt(i)->widget()) )) {
            disconnect(button, SIGNAL(clicked()), this, SLOT(SetCurrString()));
        }
        QWidget *w = widget.gridLayout->itemAt(i)->widget();
        widget.gridLayout->removeItem(widget.gridLayout->itemAt(i));
        delete w;
    }
    
    for (int i = 0; i < count; i++) {
        widget.gridLayout->addWidget(new QLabel(QString("String # %1:").arg(i+1)), i, 0);
        QPushButton *button = new QPushButton( tr(SingleToneAnalyzer::noteName(round(SingleToneAnalyzer::freq2pitch(InstrumentTypes[item].frequences[i])))) );
        widget.gridLayout->addWidget(button, i, 1);
        QLabel *value = new QLabel(QString::number(InstrumentTypes[item].frequences[i]));
        value->hide();
        widget.gridLayout->addWidget(value, i, 2);
        
        // Test
        //if (button->text().toAscii()[0] == 'D')button->hide();
        
        connect(button, SIGNAL(clicked()), this, SLOT(SetCurrString()));
    }
}

void Tuner::SetCurrString() {
    QPushButton *button = NULL;
    QLabel *value = NULL;
    
    for (int i = 0; i < widget.gridLayout->count(); i++) {
        if (( button = dynamic_cast<QPushButton*>(widget.gridLayout->itemAt(i)->widget()) )) {
            if (button->isDefault()) {
                value = dynamic_cast<QLabel*>(widget.gridLayout->itemAt(i+1)->widget());
                break;
            }
        }
    }
    
    if (value) {
        ChangeTone(
                tr(SingleToneAnalyzer::noteName(round(SingleToneAnalyzer::freq2pitch(value->text().toDouble())))),
                value->text().toDouble());
    }
}

void Tuner::ChangeTone(QString text, double tone) {
    int pos;
    
    name->setPlainText(text);
    natural = tone;
    pos = Note::FreqToOctavePos(natural);
    flat = (pos > 0 ? octave_notes[pos - 1] : natural);
    sharp = (pos < TOTAL_TONES - 1 ? octave_notes[pos + 1] : natural);
    
    pointer->hide();
}

void Tuner::Tune(bool result, double freq, int pitch, const char* note, double logPower){
    if (result) {
        //widget.TunerFreq->setText(QString::number(freq));
        //widget.TunerNote->setText(QString(note));
        
        double delta, harmonics = freq; // Due to algorithm (probably mine) bug, detected F0 is usually in lower freq. harmonics to actual input tone
        
        if (harmonics < natural) {
            harmonics *= floor((natural/harmonics) + 0.5);
        }
        
        if ( (delta = harmonics - natural) > 0) {
            delta = delta/(sharp - natural); // % deviation
            delta = (delta > 1 ? 1 : delta);
        } else {
            delta = delta/(natural - flat); // % deviation
            delta = (delta < -1 ? -1 : delta);
        }
        
        pointer->show();
        QPen pen;
        pen.setBrush(QColor((int)(fabs(delta)*200.), (int)((1. - fabs(delta))*200.), 0));
        pointer->setPen(pen);
        pointer->setRotation(delta * 45);
    }
    //std::cout << "Got signal. Lol! \n";
    //std::cout << ", frq = " << freq << ", pitch = " << pitch << ", note = " << note << ", log = " << logPower << "\n";
}