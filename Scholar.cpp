/*
 * File:   Scholar.cpp
 * Author: astral
 *
 * Created on 20 Июль 2012 г., 17:50
 */

#include "Scholar.h"

Scholar::Scholar(AudioIO *audio, SingleToneAnalyzer *sAna) {
    widget.setupUi(this);
    
    // Quit
    //QObject::connect(widget.actionExit, SIGNAL(triggered()), this, SLOT(quit()));
    
    // AudioIO, Analyzers
    //audio = new AudioIO();
    this->audio = audio;
    this->sAna = sAna;
    connect(sAna, SIGNAL(sendAnalyzerData(bool, double, int, const char*, double)), this, SLOT(SinglePitchData(bool, double, int, const char*, double)));
    active_note = NULL;
    //res = Result(); // TODO make adequate result statistics
    
    //Tuner
    QObject::connect(widget.actionTuner, SIGNAL(triggered()), this, SLOT(ShowTuner()));
    
    //BPM control
    bpm = widget.ScholarBPM->value();
    widget.ScholarBPMvalue->setText(QString::number(widget.ScholarBPM->value()));
    QObject::connect(widget.ScholarBPM, SIGNAL(valueChanged(int)), this, SLOT(ChangeBPMbySlider()));
    QObject::connect(widget.ScholarBPMvalue, SIGNAL(editingFinished()), this, SLOT(ChangeBPMbyText()));
    
    //Play state
    play_state = false;
    QObject::connect(widget.ScholarPlayState, SIGNAL(clicked()), this, SLOT(PlayStop()));
    // TODO add spacebar control
    
    //Visuals
    scene = new QGraphicsScene(this);
    widget.ScholarMainView->setScene(scene);
    widget.ScholarMainView->setRenderHint(QPainter::Antialiasing);
    widget.ScholarMainView->setAlignment(Qt::AlignLeft);
    scene->setSceneRect(widget.ScholarMainView->geometry());

    // Lesson // TODO make resizes
    // TEST
    lesson = new Lesson();
    DrawNotes();
    
    // Carriage
    carriage = new Carriage(this, bpm);
    scene->addItem(carriage);                           // TODO allow to turn off visual by options
    //carriage->setPos(lesson->GetStartingPos());//QPointF(100+VISUAL_BAR_SPACING-1, VISUAL_NOTE_VSPACING*4)); // TODO add sync
    QObject::connect(carriage, SIGNAL(Finished()), this, SLOT(CarriageFinished()));
    QObject::connect(carriage, SIGNAL(PassNote(Note*)), this, SLOT(FetchNote(Note*)));
    
    // Timer
    QObject::connect(&timer, SIGNAL(timeout()), scene, SLOT(advance()));
    RestartTimer();
    
    // Post-Preparation timer
    QObject::connect(&post_preparation_timer, SIGNAL(timeout()), this, SLOT(PostPreparation()));
    post_preparation_timer.start(100); // Should be enough to finish visual formations
}

Scholar::~Scholar() {
    audio->~AudioIO();
}

void Scholar::ShowTuner(){
    if (play_state) {
        PlayStop(); // Stop playback
    }
    
    tuner = new Tuner(audio, sAna);
    tuner->setWindowFlags(Qt::WindowStaysOnTopHint);
    tuner->show();
    //tuner->Tune();
}

void Scholar::ChangeBPMbySlider(){
    widget.ScholarBPMvalue->setText(QString::number(widget.ScholarBPM->value()));
    bpm = widget.ScholarBPM->value();
    carriage->SetBPM(bpm);
    RestartTimer();
}

void Scholar::ChangeBPMbyText(){
    unsigned value = widget.ScholarBPMvalue->text().toUInt();
    if (20 <= value && value <= 240){
        widget.ScholarBPM->setValue((int)value);
        bpm = value;
        carriage->SetBPM(bpm);
        RestartTimer();
    } else {
        ChangeBPMbySlider();
    }
}

void Scholar::PlayStop(){
    play_state = (play_state ? false : true);
    
    if (play_state) {
        widget.ScholarPlayState->setText("Playing");
        RestartTimer();
    } else {
        widget.ScholarPlayState->setText("Paused");
        timer.stop();
    }
    
    //TODO change actual playback state
    carriage->SetState(play_state);
    
    //TODO stop background music
    //TODO stop audio/visual helper
}

void Scholar::FetchNote(Note* note) {                   // TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! <-- Most importaint part!
    active_note = note;
    if (SingleNote* sn = dynamic_cast<SingleNote*>(note)) {
        // chAna->stopProcess(); // TODO
        sAna->startProcess();
    }// else if if (Chord* ch = dynamic_cast<Chord*>(note)) { // TODO
    //std::cout << sn->GetPitch() << "\n";
}

// sAna must be started and SinglePitchData() is triggered by SIGNAL; for SingleNote use only
void Scholar::SinglePitchData(bool result, double freq, int pitch, const char* note, double logPower) {
    static bool prev_value;
    
    //res.value = ( res.value ? false : true); // test
    //std::cout << " " <<res.value << "\n" << flush;
    
    if (!active_note) return;
    SingleNote* sn = dynamic_cast<SingleNote*>(active_note);
    //assert(sn);
    if (!sn) return;
    //std::cout << "freq=" << freq << ", Npitch=" << sn->GetPitch() << "; ";
    if (sn->GetPitch() == 0 && (!result || logPower < -50)) { // Rest
        res.value = true;
    } else if (result) {
        if (fabs((freq - sn->GetPitch())/freq) < 0.05) { // Note found
            //std::cout << "TRUE\n";
            res.value = true;
        } else {
            //std::cout << "false\n";
            res.value = false;
        }
        //std::cout << flush;
    } else {
        res.value = false;
    }
    
    if (prev_value != res.value) {
        prev_value = res.value;
        res.update();
    }
}

void Scholar::CarriageFinished() {
    PlayStop();
    carriage->setPos(lesson->GetStartingPos().x() - 5, lesson->GetStartingPos().y()); // -5 is to be able to see 1-st note's tail
}

void Scholar::PostPreparation() {
    ResizeSceneWidth(lesson->GetVisualLength()); // No need? Redraws automaticaly?
    post_preparation_timer.stop();
    carriage->setPos(lesson->GetStartingPos().x() - 5, lesson->GetStartingPos().y()); // -5 is to be able to see 1-st note's tail
    carriage->SetEtalon((NoteLength)(nl1 / lesson->GetBeatLength()));
    
    // TODO make adequate result statistics
    scene->addItem(&res);
    res.setPos(QPointF(100, 200));
    res.value = false;
}

void Scholar::RestartTimer() {
    static const qreal C1 = 1000*60/TICS;
    if (timer.isActive()) timer.stop();
    timer.start(floor(C1/bpm + 0.5)); // As for timer.start(1000*60 / (bpm*TICS)); Windows is bugged in precision; must be adjusted!
}

void Scholar::OpenLesson(){
    //TODO actual load lesson
    
    //ResizeSceneWidth(VALUE);
    
    // bpm = lesson->GetBPM;
    // widget.ScholarBPM->setValue(VALUE);
    ChangeBPMbySlider(); // Change lable value
}

void Scholar::closeEvent(QCloseEvent *event){ // used to close audio
    this->~Scholar();
 }

void Scholar::DrawNotes(){ // TODO Dispose!!1 Move clear and additem to Load method
    
    ResizeSceneWidth(1); // Just to align vertically; will be resized on PostPreparation()
    
    scene->clear();
    
    std::vector<QGraphicsItem*> visuals = lesson->GetVisualParts();
    for (unsigned i = 0; i < visuals.size(); i++) {
        scene->addItem(visuals.at(i));
    }
}

// Temporal solution
void Result::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    if (value) {
        painter->setBrush(QBrush(Qt::green));
    } else {
        painter->setBrush(QBrush(Qt::red));
    }
    painter->drawEllipse(boundingRect());
}