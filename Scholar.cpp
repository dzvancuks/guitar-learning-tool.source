/*
 * File:   Scholar.cpp
 * Author: astral
 *
 * Created on 20 Июль 2012 г., 17:50
 */

#include "Scholar.h"
#include "ChordAnalyzer.h"

Scholar::Scholar(AudioIO *audio, Mixer *mixer, SingleToneAnalyzer *sAna, ChordAnalyzer *chAna) {
    widget.setupUi(this);
    
    // Quit
    //QObject::connect(widget.actionExit, SIGNAL(triggered()), this, SLOT(quit()));
    
    // AudioIO, Analyzers
    //audio = new AudioIO();
    this->audio = audio;
    this->mixer = mixer;
    this->sAna = sAna;
    this->chAna = chAna;
    connect(this->sAna, SIGNAL(sendAnalyzerData(bool, double, int, const char*, double)), this, SLOT(SinglePitchData(bool, double, int, const char*, double)));
    connect(this->chAna, SIGNAL(sendAnalyzerData(float*, int)), this, SLOT(ChordData(float*, int)));
    active_note = NULL;
    //res = Result(); // TODO make adequate result statistics
    
    // Tutor and passing to/from Tutor routine
    QObject::connect(widget.actionTutor, SIGNAL(triggered()), this, SLOT(StartTutor()));

    // Menu items
    // Open
    QObject::connect(widget.actionOpen, SIGNAL(triggered()), this, SLOT(OpenLesson()));
    //Tuner
    QObject::connect(widget.actionTuner, SIGNAL(triggered()), this, SLOT(ShowTuner()));
    // "About" window
    QObject::connect(widget.actionAbout, SIGNAL(triggered()), this, SLOT(ShowAbout()));
    
    //BPM control
    bpm = widget.ScholarBPM->value();
    widget.ScholarBPMvalue->setText(QString::number(widget.ScholarBPM->value()));
    QObject::connect(widget.ScholarBPM, SIGNAL(valueChanged(int)), this, SLOT(ChangeBPMbySlider()));
    QObject::connect(widget.ScholarBPMvalue, SIGNAL(editingFinished()), this, SLOT(ChangeBPMbyText()));
    
    //Play state
    play_state = false;
    QObject::connect(widget.ScholarPlayState, SIGNAL(clicked()), this, SLOT(PlayStop()));
    // TODO add spacebar control
    
    //Volume control
    QObject::connect(widget.ScholarVolumeLvl, SIGNAL(valueChanged(int)), this, SLOT(ChangeVolume()));
    
    // Effects and sound data pump
    //effects = new EffectPump(audio, mixer, widget.centralwidget);
    widget.Effects->SetAudio(audio);
    widget.Effects->SetMixer(mixer);
    //effects->setGeometry(550, 350, 3 * (FX_VISUAL_X+10), FX_VISUAL_Y);
    //effects->show();
    QObject::connect(audio, SIGNAL(InputReady()), widget.Effects, SLOT(FetchSound()));
    QObject::connect(widget.DisableEffects, SIGNAL(clicked()), widget.Effects, SLOT(UnloadAllEffects()));
    
    // Metronome
    metronome = new Metronome(this->mixer);
    metronome->SetInterval((1000*60)/bpm);
    QObject::connect(widget.ScholarMetronomeOn, SIGNAL(toggled(bool)), this, SLOT(ChangeMetronomeState(bool)));
    
    //Visuals
    scene = new QGraphicsScene(this);
    widget.ScholarMainView->setScene(scene);
    widget.ScholarMainView->setRenderHint(QPainter::Antialiasing);
    widget.ScholarMainView->setAlignment(Qt::AlignLeft);
    scene->setSceneRect(widget.ScholarMainView->geometry());

    // Lesson
    lesson = NULL;
    
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
    //post_preparation_timer.start(100); // Should be enough to finish visual formations
}

Scholar::~Scholar() {
    sAna->stopProcess();
    chAna->stopProcess();
    
    active_note = NULL;
    
    if (lesson) {
        lesson->DeleteTrack();
        delete lesson;
    }
    
    //delete audio;
    scene->removeItem(carriage);
    scene->removeItem(&res);
    scene->clear();
}

void Scholar::closeEvent(QCloseEvent *event){ // used to close audio
    this->~Scholar();
}

void Scholar::ShowTuner(){
    if (play_state) {
        PlayStop(); // Stop playback
    }
    
    tuner = new Tuner(audio, sAna);
    QObject::connect(tuner, SIGNAL(TunerClosed()), this, SLOT(DeleteTuner()));
    tuner->setWindowFlags(Qt::WindowStaysOnTopHint);
    tuner->show();
    //tuner->Tune();
}
void Scholar::DeleteTuner() {
    QObject::disconnect(tuner, SIGNAL(TunerClosed()), this, SLOT(DeleteTuner()));
    delete tuner;
    tuner = NULL;
}

void Scholar::ChangeBPMbySlider(){
    widget.ScholarBPMvalue->setText(QString::number(widget.ScholarBPM->value()));
    bpm = widget.ScholarBPM->value();
    carriage->SetBPM(bpm);
    metronome->SetInterval((1000*60)/bpm);
    RestartTimer();
}

void Scholar::ChangeBPMbyText(){
    unsigned value = widget.ScholarBPMvalue->text().toUInt();
    if (20 <= value && value <= 240){
        widget.ScholarBPM->setValue((int)value);
        bpm = value;
        carriage->SetBPM(bpm);
        metronome->SetInterval((1000*60)/bpm);
        RestartTimer();
    } else {
        ChangeBPMbySlider();
    }
}

void Scholar::ChangeVolume(){
    mixer->SetGain((double)widget.ScholarVolumeLvl->value()/100.0);
}

void Scholar::ChangeMetronomeState(bool state) {
    metronome_state = state;
    if (!metronome_state) { // "Off" state; "on" state will be started via Sync by carriage signal
        metronome->Stop();
        QObject::disconnect(carriage, SIGNAL(NewBar()), metronome, SLOT(Sync()));
    } else {
        assert( QObject::connect(carriage, SIGNAL(NewBar()), metronome, SLOT(Sync())) );
    }
}

void Scholar::PlayStop(){
    if (!lesson) return;
    
    play_state = (play_state ? false : true);
    
    if (play_state) {
        widget.ScholarPlayState->setText("Stop"); // Playing
        RestartTimer();
        if (metronome_state) {
            metronome->Sync();
            //QObject::connect(carriage, SIGNAL(NewBar()), metronome, SLOT(Sync()));
        }
    } else {
        widget.ScholarPlayState->setText("Play"); // Paused
        metronome->Stop();
        timer.stop();
        sAna->stopProcess();
        chAna->stopProcess();
    }
    
    //TODO change actual playback state
    carriage->SetState(play_state);
    
    //TODO stop background music
    //TODO stop audio/visual helper
}

void Scholar::FetchNote(Note* note) { // Fetches note and starts appropriate tone analyzer
    active_note = note;
    if (SingleNote* sn = dynamic_cast<SingleNote*>(note)) {
        Q_UNUSED(sn);
        chAna->stopProcess();
        sAna->startProcess();
    } else if (Chord* ch = dynamic_cast<Chord*>(note)) {
        Q_UNUSED(ch);
        sAna->stopProcess();
        chAna->startProcess();
    }
}

// global variable, used temporary for current lame statistics analyzer. TODO make normal statistics
static bool prev_value;

// sAna must be started and SinglePitchData() is triggered by SIGNAL; for SingleNote use only
void Scholar::SinglePitchData(bool result, double freq, int pitch, const char* note, double logPower) {
    if (!active_note) return;
    SingleNote* sn = dynamic_cast<SingleNote*>(active_note);
    if (!sn) return;
    if (sn->GetPitch() == 0 && (!result || logPower < -50)) { // Rest
        res.value = true;
    } else if (result) {
        double harmonics = freq; // Due to algorithm (probably mine) bug, detected F0 is usually in lower freq. harmonics to actual input tone
        double note_freq = sn->GetPitch();
        
        if (harmonics < note_freq) {
            harmonics *= floor((note_freq/harmonics) + 0.5);
        }
        
        if (fabs((harmonics - note_freq)/note_freq) < 0.05) { // Note found
            res.value = true;
        } else {
            res.value = false;
        }
    } else {
        res.value = false;
    }
    
    if (prev_value != res.value) {
        prev_value = res.value;
        res.update();
    }
}
// chAna must be started and ChordData() is triggered by SIGNAL; for Chord use only
void Scholar::ChordData(float* tones_in, int count) {
    if (!active_note || !count) return;
    Chord* ch = dynamic_cast<Chord*>(active_note);
    if (!ch) return;
    
    QVector<double> *tones = new QVector<double>();
    QVector<double> *chord_tones = new QVector<double>(ch->GetChordTones());
    int uninitialized_tones = 0;
    for(int i = 0; i < count; i++) { // copy out
        tones->push_back(tones_in[i]);
    }
    // Move tones 1 by 1 into u_t (10% error rate allowed, though). Empty vector - success
    while (!chord_tones->empty()) {
        int i;
        bool found = false;
        
        double curr_ch = chord_tones->at(0);
        for(i = 0; i < count; i++) { // TODO make "< count - 1", as lust tone should be bogous, but possoble
            double err, curr_tone = tones->at(i);
            if (curr_tone > chord_tones->first()) {
                err = curr_tone - curr_ch * floor((curr_tone / curr_ch) + 0.5); // i.e. 220 - 109 * (220/109) = 220 - 218 = 2
            } else {
                err = curr_ch - curr_tone * floor((curr_ch / curr_tone) + 0.5);
            }
            if (fabs(err / curr_tone) < 0.1) { // algorithms 10% err rate
                found = true;
                break;
            }
        }

        if (!found) {
            uninitialized_tones++;
        }
        //if(chord_tones->size() == 1) break; // avoid next line, as it loops cycle (!)
        chord_tones->pop_front();
    }
    
    res.value = (uninitialized_tones ? true : false);
    if (prev_value != res.value) {
        prev_value = res.value;
        res.update();
    }
    
    delete tones;
    delete chord_tones;
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
    
    scene->update();
    
    // TODO make adequate result statistics
    if (!res.scene()) scene->addItem(&res);
    res.setPos(QPointF(80, 20));
    res.value = false;
   
    /*
    // Test
    std::vector<double> tones;
    tones.push_back(440);
    tones.push_back(261.626);
    //tones.push_back(246.942);
    tones.push_back(220);
    Chord *c = new Chord(tones, nl16, 0);
    //c->setPos(200, 100);
    scene->addItem(c);
    lesson->GetTrack()->GetBars().at(0)->AddNoteBack(c);
    c->update();
    */
}

void Scholar::RestartTimer() {
    static const qreal C1 = 1000*60/TICS;
    if (timer.isActive()) timer.stop();
    timer.start(floor(C1/bpm + 0.5)); // As for timer.start(1000*60 / (bpm*TICS)); Windows is bugged in precision; must be adjusted!
}

void Scholar::OpenLesson(){
    QString file_name = QFileDialog::getOpenFileName(this,
         tr("Save Guitar Lesson"), "",
         tr("Guitar Learning Tool (*.glt);;All Files (*)")); // TODO add gp3 and TAB txt format support
    if (file_name.isEmpty())
        return;
    else {
        QFile file(file_name);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
                return;
        }
        LoadStore::Load(&lesson, &file);
        file.close();
    }
    
    if (!lesson) return;
    
    //ResizeSceneWidth(VALUE);
    
    // bpm = lesson->GetBPM();
    widget.ScholarBPM->setValue(lesson->GetBPM());
    ChangeBPMbySlider(); // Change lable value
    
    scene->removeItem(&res);
    scene->removeItem(carriage);
    
    scene->clear();
    scene->addItem(carriage);
    std::vector<QGraphicsItem*> visuals = lesson->GetVisualParts();
    for (unsigned i = 0; i < visuals.size(); i++) {
        scene->addItem(visuals.at(i));
    }

    post_preparation_timer.start(100); // Should be enough to finish visual formations
    // ResizeSceneWidth, GetVisualParts, etc HERE; see FetchFromTutor()
    // post_preparation_timer.start(100); // Should be enough to finish visual formations
}

void Scholar::StartTutor() {
    emit PassToTutor(lesson);
    this->hide();
}

void Scholar::FetchFromTutor(Lesson* nlesson) {
    this->show();
    
    if (!nlesson) return;
    if (!lesson) {
        lesson = nlesson;
    } else if (lesson != nlesson) { // Different pointers (?)
        lesson->DeleteTrack();
        delete lesson;
        lesson = nlesson;
    }
    
    //ResizeSceneWidth(1); // Just to align vertically; will be resized on PostPreparation()
    // BUG to bugreports.qt-project.org is reported: scene->clear() and scene->addItem(carriage, &res) crashes program
    scene->removeItem(&res);
    scene->removeItem(carriage);
    
    scene->clear();
    scene->addItem(carriage);
    std::vector<QGraphicsItem*> visuals = lesson->GetVisualParts();
    for (unsigned i = 0; i < visuals.size(); i++) {
        scene->addItem(visuals.at(i));
    }

    post_preparation_timer.start(100); // Should be enough to finish visual formations
}

/*
void Scholar::DrawNotes(){ // TODO Dispose!!1 Move clear and additem to Load method
    
    ResizeSceneWidth(1); // Just to align vertically; will be resized on PostPreparation()
    
    scene->clear();
    
    std::vector<QGraphicsItem*> visuals = lesson->GetVisualParts();
    for (unsigned i = 0; i < visuals.size(); i++) {
        scene->addItem(visuals.at(i));
    }
}
*/

// Temporal solution
void Result::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
    if (value) {
        painter->setBrush(QBrush(Qt::green));
    } else {
        painter->setBrush(QBrush(Qt::red));
    }
    painter->drawEllipse(boundingRect());
}