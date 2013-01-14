/*
 * File:   Tutor.cpp
 * Author: astral
 *
 * Created on 10 Октябрь 2012 г., 20:22
 */

#include "Tutor.h"

Tutor::Tutor(AudioIO *audio) {
    widget.setupUi(this);
    widget.ToneStringVal->clear();
    widget.ToneStringVal->insertItems(0, QStringList()
         << QApplication::translate("Tutor", "N/A", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Tutor", "1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Tutor", "2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Tutor", "3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Tutor", "4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Tutor", "5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("Tutor", "6", 0, QApplication::UnicodeUTF8)
    );
    
    // AudioIO
    this->audio = audio;
    
    
    
    //Visuals
    scene = new QGraphicsScene(this);
    widget.TutorMainView->setScene(scene);
    widget.TutorMainView->setRenderHint(QPainter::Antialiasing);
    widget.TutorMainView->setAlignment(Qt::AlignLeft);
    scene->setSceneRect(widget.TutorMainView->geometry());
    //scene->setSceneRect( 0, 0, 1000, 1000 );
    scene->installEventFilter( this );
    
    // Scholar and passing to/from Scholar routine
    QObject::connect(widget.actionScholar, SIGNAL(triggered()), this, SLOT(StartScholar()));
    
    // Menu items
    file_name = QString("");
    // New file
    QObject::connect(widget.actionNew, SIGNAL(triggered()), this, SLOT(New()));
    // Save
    QObject::connect(widget.actionSave, SIGNAL(triggered()), this, SLOT(Save()));
    // Save As
    QObject::connect(widget.actionSave_As, SIGNAL(triggered()), this, SLOT(SaveAs()));
    // Open
    QObject::connect(widget.actionOpen, SIGNAL(triggered()), this, SLOT(Open()));
    // "About" window
    QObject::connect(widget.actionAbout, SIGNAL(triggered()), this, SLOT(ShowAbout()));
    
    // Editor's panel buttons
    // Track
    QObject::connect(widget.TrackBPMVal, SIGNAL(valueChanged(int)), this, SLOT(BPMChanged(int)));
    QObject::connect(widget.TrackBeatCountVal, SIGNAL(valueChanged(int)), this, SLOT(BCChanged(int)));
    QObject::connect(widget.TrackBeatLengthVal, SIGNAL(valueChanged(int)), this, SLOT(BLChanged(int)));
    QObject::connect(widget.TrackClefVal, SIGNAL(currentIndexChanged(int)), this, SLOT(ClefChanged(int)));
    // Bar
    QObject::connect(widget.BarAddBtn, SIGNAL(clicked()), this, SLOT(AddBar()));
    QObject::connect(widget.BarRemoveBtn, SIGNAL(clicked()), this, SLOT(DelBar()));
    QObject::connect(widget.BarShiftRightBtn, SIGNAL(clicked()), this, SLOT(ShiftRightBar()));
    QObject::connect(widget.BarShiftLeftBtn, SIGNAL(clicked()), this, SLOT(ShiftLeftBar()));
    QObject::connect(widget.BarRepeatStartVal, SIGNAL(stateChanged(int)), this, SLOT(RepeatStart(int)));
    QObject::connect(widget.BarRepeatCountVal, SIGNAL(valueChanged(int)), this, SLOT(RepeatEnd(int)));
    QObject::connect(widget.BarRepeatNextEndVal, SIGNAL(stateChanged(int)), this, SLOT(RepeatOnNext(int)));
    QObject::connect(widget.BarChordVal, SIGNAL(editingFinished()), this, SLOT(BarChord()));
    // Note
    QObject::connect(widget.NoteAddBtn, SIGNAL(clicked()), this, SLOT(AddNote()));
    QObject::connect(widget.NoteRemoveBtn, SIGNAL(clicked()), this, SLOT(DelNote()));
    QObject::connect(widget.NoteShiftRightBtn, SIGNAL(clicked()), this, SLOT(ShiftRightNote()));
    QObject::connect(widget.NoteShiftLeftBtn, SIGNAL(clicked()), this, SLOT(ShiftLeftNote()));
    QObject::connect(widget.NoteLengthVal, SIGNAL(valueChanged(int)), this, SLOT(NoteLength(int)));
    QObject::connect(widget.NoteExtensionVal, SIGNAL(valueChanged(int)), this, SLOT(NoteExtension(int)));
    QObject::connect(widget.NoteContinueVal, SIGNAL(valueChanged(int)), this, SLOT(NoteContinue(int)));
    QObject::connect(widget.NoteSlideVal, SIGNAL(valueChanged(int)), this, SLOT(NoteSlide(int)));
    QObject::connect(widget.NoteVibratoVal, SIGNAL(valueChanged(int)), this, SLOT(NoteVibrato(int)));
    QObject::connect(widget.NoteGrouppingVal, SIGNAL(valueChanged(int)), this, SLOT(NoteGrouping(int)));
    QObject::connect(widget.NoteUngrouppingVal, SIGNAL(valueChanged(int)), this, SLOT(NoteUngrouping(int)));
    QObject::connect(widget.NoteHOPOOffRadio, SIGNAL(valueChanged(int)), this, SLOT(NoteHOPO(int))); // TODO make 3 connections
    // Tone
    QObject::connect(widget.ToneAddBtn, SIGNAL(clicked()), this, SLOT(AddTone()));
    QObject::connect(widget.ToneRemoveBtn, SIGNAL(clicked()), this, SLOT(DelTone()));
    QObject::connect(widget.ToneUpBtn, SIGNAL(clicked()), this, SLOT(ToneUp()));
    QObject::connect(widget.ToneDownBtn, SIGNAL(clicked()), this, SLOT(ToneDown()));
    QObject::connect(widget.ToneStringVal, SIGNAL(currentIndexChanged(int)), this, SLOT(ToneString(int)));
    QObject::connect(widget.ToneRestVal, SIGNAL(stateChanged(int)), this, SLOT(ToneRest(int)));
    
    // Play buttons
    QObject::connect(widget.TrackPlayBtn, SIGNAL(clicked()), this, SLOT(TrackPlay()));
    QObject::connect(widget.BarPlayBtn, SIGNAL(clicked()), this, SLOT(BarPlay()));
    QObject::connect(widget.NotePlayBtn, SIGNAL(clicked()), this, SLOT(NotePlay()));

    lesson = NULL;
    track = NULL;
    active_bar = NULL;
    active_note1 = NULL;
    active_note2 = NULL;
    widget.TrackEditFrame->setDisabled(true);
    widget.BarEditFrame->setDisabled(true);
    widget.NoteEditFrame->setDisabled(true);
    widget.ToneFrame->setDisabled(true);
}

Tutor::~Tutor() {
    if (lesson) {
        lesson->DeleteTrack();
        delete lesson;
    }
    
    //delete audio;
    scene->clear();
}

void Tutor::closeEvent(QCloseEvent *event){ // used to close audio
    this->~Tutor();
 }

// few functions to change enable/disabled state for widgets. NB Change implementation in widget change
void Tutor::ChangeBarWidgetFrame(bool state) {
    widget.BarAddBtn->setEnabled(true); // Always on, no matter what; disabled only with frame
    widget.BarEditFrame->setEnabled(state);
}
void Tutor::ChangeBarWidgetFrameAllButAddBtn(bool state) { // Used if frame is selected/not
    widget.BarPlayBtn->setEnabled(state);
    widget.BarRemoveBtn->setEnabled(state);
    widget.BarRemoveBtn->setEnabled(state);
    widget.BarShiftLeftBtn->setEnabled(state);
    widget.BarShiftRightBtn->setEnabled(state);
    widget.BarRepeatStartVal->setEnabled(state);
    widget.BarRepeatCountVal->setEnabled(state);
    widget.BarRepeatNextEndVal->setEnabled(state);
    widget.BarChordVal->setEnabled(state);
}

void Tutor::ChangeNoteWidgetFrame(bool state) {
    widget.NoteAddBtn->setEnabled(true); // Always on, no matter what; disabled only with frame
    widget.NoteEditFrame->setEnabled(state);
}
void Tutor::ChangeNoteWidgetFrameAllButAddBtn(bool state) {
    widget.NotePlayBtn->setEnabled(state);
    widget.NoteRemoveBtn->setEnabled(state);
    widget.NoteShiftLeftBtn->setEnabled(state);
    widget.NoteShiftRightBtn->setEnabled(state);
    widget.NoteLengthVal->setEnabled(state);
    widget.NoteExtensionVal->setEnabled(state);
    widget.NoteContinueVal->setEnabled(false); // Enabled only when 2 notes selected
    widget.NoteSlideVal->setEnabled(false);    // Enabled only when 2 notes selected
    widget.NoteVibratoVal->setEnabled(state);
    widget.NoteGrouppingVal->setEnabled(state);
    widget.NoteUngrouppingVal->setEnabled(state);
    //widget.NoteHOPOOffRadio->setEnabled(state); // TODO 3 handlers
}
void Tutor::ChangeToneWidgetFrame(bool state) {
    SingleNote* sn;
    Chord *ch;
    if ((active_note1 && active_note2) || (!active_note1 && !active_note2)) {
        widget.ToneFrame->setEnabled(false);
    } else if (active_note1) { // working with one active note
        if ((ch = dynamic_cast<Chord*> (active_note1) )) { // TODO no rest; if tone count = 6, disable 'add'
            widget.ToneAddBtn->setEnabled((ch->GetChordTones().count() >= MAX_SUBNOTES ? false : true ));
            widget.ToneRemoveBtn->setEnabled((ch->GetChordTones().count() < 2 ? false : true ));
            widget.ToneRestVal->setEnabled(false);
            Subnote *st = ch->CurrSubtone();
            if (!st) {
                widget.ToneUpBtn->setDisabled(true);
                widget.ToneDownBtn->setDisabled(true);
                widget.ToneRestVal->setChecked(true);
                widget.ToneStringVal->setDisabled(true);
                widget.ToneStringVal->setCurrentIndex(0);
            } else {
                widget.ToneUpBtn->setEnabled(true);
                widget.ToneDownBtn->setEnabled(true);
                widget.ToneRestVal->setChecked(false);
                widget.ToneStringVal->setEnabled(true);
                widget.ToneStringVal->setCurrentIndex((int)st->string);
            }
        } else if ((sn = dynamic_cast<SingleNote*> (active_note1) )) {
            widget.ToneAddBtn->setEnabled(true); // make it TRUE after Chord system implementation
            widget.ToneRemoveBtn->setDisabled(true);
            widget.ToneRestVal->setEnabled(true);
            if (sn->GetPitch() == 0) { // Rest
                widget.ToneUpBtn->setDisabled(true);
                widget.ToneDownBtn->setDisabled(true);
                widget.ToneRestVal->setChecked(true);
                widget.ToneStringVal->setDisabled(true);
                widget.ToneStringVal->setCurrentIndex(0);
            } else {
                widget.ToneUpBtn->setEnabled(true);
                widget.ToneDownBtn->setEnabled(true);
                widget.ToneRestVal->setChecked(false);
                widget.ToneStringVal->setEnabled(true);
                widget.ToneStringVal->setCurrentIndex((int)sn->GetString());
            }
        }
        widget.ToneFrame->setEnabled(state);
    } else  { // none selected
        widget.ToneFrame->setEnabled(false);
    }// else if (note && ch = dynamic_cast<Chord*>note) {} //TODO
}

void Tutor::New() {
    if (lesson) {
        lesson->DeleteTrack();
        delete lesson;
    }
    
    scene->clear();
    ResizeSceneWidth(1); // To make proper vertical alignment
    lesson = new Lesson();
    track = new Track(treble, DEFAULT_BEAT_COUNT, DEFAULT_BEAT_LEN);
    
    lesson->SetTrack(track);
    lesson->SetBPM(DEFAULT_BPM);
    track->SetClef(DEFAULT_CLEF); // DEFAULT_CLEF
    track->SetBeatCount(DEFAULT_BEAT_COUNT);
    track->SetBeatLength(DEFAULT_BEAT_LEN);
    // Every other entities (bar and two notes) are gathered by mouse clicking

    std::vector<QGraphicsItem*> visuals = lesson->GetVisualParts();
    for (unsigned i = 0; i < visuals.size(); i++) {
        scene->addItem(visuals.at(i));
    }
    ResizeSceneWidth(lesson->GetVisualLength());
    
    // Set Editor's active values
    widget.TrackEditFrame->setEnabled(true);
    widget.TrackPlayBtn->setEnabled(true);
    widget.TrackBPMVal->setValue(lesson->GetBPM());
    widget.TrackClefVal->setCurrentIndex( (track->GetClef() == DEFAULT_CLEF ? 0 : 1) );
    widget.TrackBeatCountVal->setValue(track->GetBeatCount());
    widget.TrackBeatLengthVal->setValue(track->GetBeatLength());
    // On NEW Lesson every other component should be turned off
    ChangeBarWidgetFrameAllButAddBtn(false);
    ChangeBarWidgetFrame(true);
}

void Tutor::Open() {
    file_name = QFileDialog::getOpenFileName(this,
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
    
    track = lesson->GetTrack();
    scene->clear();
    std::vector<QGraphicsItem*> visuals = lesson->GetVisualParts();
    for (unsigned i = 0; i < visuals.size(); i++) {
        scene->addItem(visuals.at(i));
    }
    ResizeSceneWidth(lesson->GetVisualLength());
    
    // Set Editor's active values
    widget.TrackEditFrame->setEnabled(true);
    widget.TrackPlayBtn->setEnabled(true);
    widget.TrackBPMVal->setValue(lesson->GetBPM());
    widget.TrackClefVal->setCurrentIndex( (track->GetClef() == DEFAULT_CLEF ? 0 : 1) );
    widget.TrackBeatCountVal->setValue(track->GetBeatCount());
    widget.TrackBeatLengthVal->setValue(track->GetBeatLength());
    // On Loaded Lesson every other component should be turned off
    ChangeBarWidgetFrameAllButAddBtn(false);
    ChangeBarWidgetFrame(true);
}

void Tutor::Save() {
    if (file_name.isEmpty()) {
        SaveAs();
    } else {
        QFile file(file_name);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
                return;
        }
        LoadStore::Store(lesson, &file);
        file.close();
    }
}

void Tutor::SaveAs() {
    if (!lesson) return;
    
    file_name = QFileDialog::getSaveFileName(this,
         tr("Save Guitar Lesson"), "",
         tr("Guitar Learning Tool (*.glt);;All Files (*)")); // TODO add gp3 and TAB txt format support
    if (file_name.isEmpty())
        return;
    else {
        QFile file(file_name);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
                return;
        }
        LoadStore::Store(lesson, &file);
    }
}

// Editor's panel button signal handlers
// Track
void Tutor::BPMChanged(int val) {
    if (!lesson) { return; }
    
    if (val < 20) { val = 20; }
    if (val > 240) { val = 240; }
    lesson->SetBPM(val);
    widget.TrackBPMVal->setValue(lesson->GetBPM());
} 
void Tutor::BCChanged(int val) {
    if (!track) { return; }
    
    if (val < 1) { val = 1; }
    if (val > 99) { val = 99; }
    track->SetBeatCount(val);
    track->RecalculateAllBarsLength();
    ResizeSceneWidth(lesson->GetVisualLength());
    track->update();
    SceneUpdate();
    widget.TrackBeatCountVal->setValue(track->GetBeatCount());
    
    // TODO foreach bar in track, update length >> track->RecalculateAllBarsLength()
}
void Tutor::BLChanged(int val) {
    static int prev_value = 0;
    if (!track) { return; }
    
    // on every step jump to nearest exponential value: 16->17 >> 32, 16->15 >> 8
    // To simplify exponential value check on increment/decrement, it's easier to use switch clause
    if (prev_value) { // already initialised
        if (prev_value < val) { // change up
            switch (val) {
                case 2: break;
                case 3: val = 4; break;
                case 5: val = 8; break;
                case 9: val = 16; break;
                case 17: val = 32; break;
                case 33: val = 64; break;
                default: val = prev_value;
            }
        } else { // change down
            switch (val) {
                case 63: val = 32; break;
                case 31: val = 16; break;
                case 15: val = 8; break;
                case 7: val = 4; break;
                case 3: val = 2; break;
                case 1: break;
                default: val = prev_value;
            }
        }
    }
    // additional check if value is set manually; 
    if (val < 1) { val = 1; }
    if (val > 64) { val = 64; }
    if (val != 1 && val != 2 && val != 4 && val != 8 && val != 16 && val != 32 && val != 64) {
        val = qPow(2, round(log2(val)));
    }
    prev_value = val;
     
    track->SetBeatLength(val);
    track->RecalculateAllBarsLength();
    ResizeSceneWidth(lesson->GetVisualLength());
    //track->update();
    SceneUpdate();
    widget.TrackBeatLengthVal->setValue(track->GetBeatLength());
    
    // TODO foreach bar in track, update length >> track->RecalculateAllBarsLength()
}
void Tutor::ClefChanged(int val) {
    if (!track) { return; }
    track->SetClef( (val == 0 ? treble : bass) ); // Every bar's clef updated by Track
    track->update();
    widget.TrackClefVal->setCurrentIndex( (track->GetClef() == DEFAULT_CLEF ? 0 : 1) );
    
    // TODO update each bar!
}
// Bar
void Tutor::AddBar() { // TODO make 'add BEFORE', or something like after Track beginning
    Bar *tmpbar;
    bool was_last;
    if (active_bar) was_last = active_bar->IsLast(); // new Bar() removes this value
    else was_last = false;
    
    tmpbar = new Bar(track->CalculateBarLength());
    if (!active_bar) {
        track->AddBarBack(tmpbar);
        scene->addItem(tmpbar);
    } else {
        if (was_last) {
            track->AddBarBack(tmpbar); // Automatically handles Prev/Next bar
            scene->addItem(tmpbar);
        } else { // insert AFTER active
            //unsigned id = active_bar->GetNextBar()->GetId();
            
            //tmpbar->StichPointers(active_bar, active_bar->GetNextBar()) // Automatically handled by track->AddBarAt
            track->AddBarAt(tmpbar, active_bar->GetId()); // bar and next bar ID will be adjusted automatically
            scene->addItem(tmpbar);
        }
        if (active_bar->GetNextRepeatEndingId() && active_bar->RepeatEndCount()) {
            widget.BarRepeatNextEndVal->setEnabled(true);
        } else {
            widget.BarRepeatNextEndVal->setDisabled(true);
        }
    }
    ResizeSceneWidth(lesson->GetVisualLength());
    SceneUpdate();
    
    assert(QObject::connect(tmpbar, SIGNAL(NoteSubstituted(Note*, Note*)), this, SLOT(SubstituteNote(Note*, Note*))) );
}
void Tutor::DelBar() {
    if (!active_bar) return;
    
    track->RemoveBarAt(active_bar->GetId() -1); // -1 as for vector indexing starts from 0; id handling and pointer stitching is handled by Track
    delete active_bar;
    active_bar = NULL;
    active_note1 = active_note2 = NULL;
    ChangeBarWidgetFrameAllButAddBtn(false);
    ResizeSceneWidth(lesson->GetVisualLength());
    SceneUpdate();
}
void Tutor::ShiftRightBar() { // TODO update widget for RS, RE
    if (!track || !active_bar) return;
    if (active_bar->IsLast()) return;

    if (active_bar->GetNextRepeatEndingId()) {
        active_bar->SetNextRepeatEndingId(0);
    } else if (active_bar->GetPrevBar() && active_bar->GetPrevBar()->GetNextRepeatEndingId() != 0) {
        active_bar->GetPrevBar()->SetNextRepeatEndingId(0);
    }
    track->SwapBars(active_bar, active_bar->GetNextBar());
    SceneUpdate();
}
void Tutor::ShiftLeftBar() { // TODO update widget for RS, RE
    if (!track || !active_bar) return;
    if (active_bar->GetId() == 1) return;

    if (active_bar->GetNextRepeatEndingId()) {
        active_bar->SetNextRepeatEndingId(0);
    } else if (active_bar->GetPrevBar() && active_bar->GetPrevBar()->GetNextRepeatEndingId() != 0) {
        active_bar->GetPrevBar()->SetNextRepeatEndingId(0);
    }
    track->SwapBars(active_bar->GetPrevBar(), active_bar);
    SceneUpdate();
}
void Tutor::RepeatStart(int val){
    if (!active_bar) return;
    
    active_bar->SetRepeatStart((val!=0 ? true : false));
    active_bar->update();
}
void Tutor::RepeatEnd(int val) {
    //NB RE 1 === 0;
    if (!active_bar) return;
    
    active_bar->SetRepeatEnd((unsigned)val);
    if ( active_bar->IsLast() ||
         (active_bar->GetPrevBar() && active_bar->GetPrevBar()->GetNextRepeatEndingId() == active_bar->GetId()) || // Flag already set on prev Bar
         val != 2) {                                                                                               // Or RC is not 2
        widget.BarRepeatNextEndVal->setDisabled(true);
    } else {
        widget.BarRepeatNextEndVal->setEnabled(true);
    }
    active_bar->update();
}
void Tutor::RepeatOnNext(int val) {
    if (!active_bar) return;
    
    if (val == 0) {
        active_bar->SetNextRepeatEndingId(0);
        active_bar->update();
        if (active_bar->GetNextBar()) active_bar->GetNextBar()->update();
    } else if ( !active_bar->IsLast() &&
                active_bar->RepeatEndCount() == 2 && //active_bar->GetNextBar()==!islast && // RC is 2 and Bar has neighbour to the right
                (active_bar->GetId() == 1 || (active_bar->GetPrevBar() && active_bar->GetPrevBar()->GetNextRepeatEndingId() == 0) ) // Flag was not set on prev Bar
              ) {
        active_bar->SetNextRepeatEndingId(active_bar->GetNextBar()->GetId());
        active_bar->update();
        active_bar->GetNextBar()->update();
    }
}
void Tutor::BarChord() {
    if (!active_bar) return;
    
    active_bar->SetBarChord(widget.BarChordVal->text()); // Cant set widget 
    active_bar->update();
}
// Note
void Tutor::AddNote() {
    SingleNote *tmpnote;
    
    //if (!active_note1) return;
    if (!active_bar) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
    
    tmpnote = new SingleNote(nl1, 0, (track->GetClef() == treble ? 440.0 : 110) );
    if (!active_note1) {
        active_bar->AddNoteBack(tmpnote);
    } else {
        active_bar->AddNoteAfterNote(tmpnote, active_note1);
    }
    scene->addItem(tmpnote);
    
    ResizeSceneWidth(lesson->GetVisualLength());
    SceneUpdate();
}
void Tutor::DelNote() {
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
    
    active_bar->RemoveNote(active_note1);
    delete active_note1;
    active_note1 = NULL;
    ChangeNoteWidgetFrameAllButAddBtn(false);
    ResizeSceneWidth(lesson->GetVisualLength());
    SceneUpdate();
}
void Tutor::ShiftRightNote() {
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
    
    if (!active_bar->NoteIsLast(active_note1)) {
        int pos = active_bar->RemoveNote(active_note1);
        if (pos >= 0) {
            active_bar->AddNoteAt(active_note1, pos+1);
            SceneUpdate();
        }
    }
}
void Tutor::ShiftLeftNote() {
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
    
    if (!active_bar->NoteIsFirts(active_note1)) {
        int pos = active_bar->RemoveNote(active_note1);
        if (pos >= 0) {
            active_bar->AddNoteAt(active_note1, pos-1);
            SceneUpdate();
        }
    }
}
void Tutor::NoteLength(int val) {
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
    
    enum NoteLengthE curr = (enum NoteLengthE) (64/val); // NB enum NoteLengthE 64 = whole note, 1 = 64-th
    enum NoteLengthE prev_value = active_note1->GetBasicLength(); // TODO rename, see Note.h
    
    // on every step jump to nearest exponential value: 16->17 >> 32, 16->15 >> 8
    // To simplify exponential value check on increment/decrement, it's easier to use switch clause
    if (prev_value > curr) { // change up, NB enum NoteLengthE 64 = whole note, 1 = 64-th
        switch (val) {
            case 2: break;
            case 3: val = 4; break;
            case 5: val = 8; break;
            case 9: val = 16; break;
            case 17: val = 32; break;
            case 33: val = 64; break;
            default: val = 64/(int)prev_value;
        }
    } else { // change down
        switch (val) {
            case 63: val = 32; break;
            case 31: val = 16; break;
            case 15: val = 8; break;
            case 7: val = 4; break;
            case 3: val = 2; break;
            case 1: break;
            default: val = 64/(int)prev_value;
        }
    }
    // additional check if value is set manually; 
    if (val < 1) { val = 1; }
    if (val > 64) { val = 64; }
    if (val != 1 && val != 2 && val != 4 && val != 8 && val != 16 && val != 32 && val != 64) {
        val = qPow(2, round(log2(val)));
    }
    curr = (enum NoteLengthE) (64/val);
     
    active_note1->SetLength(curr);
    ResizeSceneWidth(lesson->GetVisualLength());
    //active_note1->update();
    //active_bar->update();
    SceneUpdate();
    widget.NoteLengthVal->setValue(val);
}
void Tutor::NoteExtension(int val) {
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected

    if (val < 0) val = 0;
    if (val > 2) val = 2;
    
    active_note1->SetExtension((unsigned)val);
    ResizeSceneWidth(lesson->GetVisualLength());
    //active_note1->update();
    //active_bar->update();
    SceneUpdate();
    widget.NoteExtensionVal->setValue(val);
} 
void Tutor::NoteContinue(int val) {
    if (!active_note1 && !active_note2) return; // 2 notes must be selected
    // TODO, additional check for 2 active (selected) notes must be performed; must be LAST note in bar# and FIRST note in bar#+1
} 
void Tutor::NoteSlide(int val) {
    if (!active_note1 && !active_note2) return; // 2 notes must be selected
    // TODO, additional check for 2 active (selected) notes must be performed
} 
void Tutor::NoteVibrato(int val) {
    if (!active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
}
void Tutor::NoteGrouping(int val) {
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
}
void Tutor::NoteUngrouping(int val) {
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
}
void Tutor::NoteHOPO(int val) {
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
    // TODO make 3 slots??
} 
// Tone
void Tutor::AddTone() {
    if (!active_bar || !active_note1) return;
    SingleNote* sn;
    Chord *ch;
    
    if ((sn = dynamic_cast<SingleNote*> (active_note1))) {
        //scene->removeItem(active_note1);
        active_bar->SNToChord(active_note1); // will be continued in AddToneSN_Chord
    } else if ((ch = dynamic_cast<Chord*> (active_note1))) {
        ch->AddTone(); // next higher possible
        SceneUpdate();
    }
}
void Tutor::AddToneSN_Chord() { // used after note substitution
    if (!active_bar || !active_note1) return;
    Chord *ch;
    if ((ch = dynamic_cast<Chord*> (active_note1))) {
        ch->AddTone(); // next higher possible
        
        if (ch->GetChordTones().count() >= MAX_SUBNOTES) {
            widget.ToneAddBtn->setEnabled(false);
        }
        
        SceneUpdate();
    }
}
void Tutor::DelTone() {
    if (!active_bar || !active_note1) return;
    Chord *ch;
    if ((ch = dynamic_cast<Chord*> (active_note1))) {
        ch->RemoveCurrSubnote(); // if possible
        SceneUpdate();
    }
}
void Tutor::ToneUp() {
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
    
    SingleNote* sn;
    Chord *ch;
    double pitch = 0;
     
    if ((ch = dynamic_cast<Chord*> (active_note1) )) {
        ch->RaiseCurrSubnote();
        SceneUpdate();
    } else if ((sn = dynamic_cast<SingleNote*> (active_note1) )) {
        pitch = sn->GetPitch();
    }
    if (!pitch) return; // Rest, Chord or error
    
    int tone_global_pos; // position in octave_notes
    double e = 0.1; // error rate
    for (tone_global_pos = 0; tone_global_pos <= TOTAL_TONES; tone_global_pos++) { // search tone shift
        double diff = octave_notes[tone_global_pos] - pitch;
        if (diff < 0) diff = -diff;
        if (diff < e) break;
    }
    if (tone_global_pos == TOTAL_TONES) return; // Not found?
    
    if (tone_global_pos < TOTAL_TONES - 1) {
        if (sn) {
            sn->SetPitch(octave_notes[tone_global_pos+1]);
        } // else if(ch) {} else {ERROR}
    }
    
    SceneUpdate();
}
void Tutor::ToneDown(){
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
    
    SingleNote* sn;
    Chord *ch;
    double pitch = 0;
     
    if ((ch = dynamic_cast<Chord*> (active_note1) )) {
        ch->LowerCurrSubnote();
        SceneUpdate();
    } else if ((sn = dynamic_cast<SingleNote*> (active_note1) )) {
        pitch = sn->GetPitch();
    }
    if (!pitch) return; // Rest, Chord or error
    
    int tone_global_pos; // position in octave_notes
    double e = 0.1; // error rate
    for (tone_global_pos = 0; tone_global_pos <= TOTAL_TONES; tone_global_pos++) { // search tone shift
        double diff = octave_notes[tone_global_pos] - pitch;
        if (diff < 0) diff = -diff;
        if (diff < e) break;
    }
    if (tone_global_pos == TOTAL_TONES) return; // Not found?
    
    if (tone_global_pos > 0) {
        if (sn) {
            sn->SetPitch(octave_notes[tone_global_pos-1]);
        } // else if(ch) {} else {ERROR}
    }
    
    SceneUpdate();
}
void Tutor::ToneString(int val){
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
    
    SingleNote* sn;
    Chord* ch;
    if ((sn = dynamic_cast<SingleNote*> (active_note1) )) {
        sn->SetString((unsigned)val);
    } else if ((ch = dynamic_cast<Chord*> (active_note1) )) {
        ch->ModifyCurrSubnote((unsigned)val);
    }
    
    // Must be updated, since TAB is outside Bar's boundingRect
    scene->update();
}
void Tutor::ToneRest(int val) {
    if (!active_bar || !active_note1) return;
    if (active_note1 && active_note2) return; // must be only 1 note selected
    
    SingleNote* sn;
    //Chord *ch; // TODO
    //if ((ch = dynamic_cast<SingleNote*> (active_note1) )) { return } else // TODO only SingleNote may be rested
    if ((sn = dynamic_cast<SingleNote*> (active_note1) )) {
        if (val != 0) { // checked
            sn->SetPitch(0);
            widget.ToneUpBtn->setDisabled(true);
            widget.ToneDownBtn->setDisabled(true);
            widget.ToneStringVal->setDisabled(true);
            widget.ToneStringVal->setCurrentIndex(0);
        } else {
            widget.ToneUpBtn->setEnabled(true);
            widget.ToneDownBtn->setEnabled(true);
            sn->SetPitch((track->GetClef() == treble ? 440.0 : 110)); // TODO make toggled with prev val
            widget.ToneStringVal->setEnabled(true);
            widget.ToneStringVal->setCurrentIndex(0); // also reset, TODO make toggled with prev val
        }
        
        SceneUpdate();
    }
}

void Tutor::BarSelected(Bar* bar){ // TODO handle 'clear' selection
    active_bar = bar;
    
    // Bar editor
    ChangeBarWidgetFrameAllButAddBtn(true);
    widget.BarRepeatStartVal->setChecked(active_bar->IsRepeatStart());
    if (active_bar->GetId() == 1) {
        widget.BarRepeatStartVal->setDisabled(true);
    } else {
        widget.BarRepeatStartVal->setEnabled(true);
    }
    widget.BarRepeatCountVal->setValue((int)active_bar->RepeatEndCount());
    widget.BarRepeatNextEndVal->setChecked((active_bar->GetNextRepeatEndingId() != 0 ? true : false));
    if (active_bar->IsLast() || active_bar->RepeatEndCount() != 2 ||                                              // RC is not 2
        (active_bar->GetPrevBar() && active_bar->GetPrevBar()->GetNextRepeatEndingId() == active_bar->GetId()) || // or flag already set on prev Bar
        (active_bar->GetNextBar() && active_bar->GetNextBar()->GetNextRepeatEndingId()) ) {                        // or next bar already has RN
        widget.BarRepeatNextEndVal->setDisabled(true);
    } else {
        widget.BarRepeatNextEndVal->setEnabled(true);
    }
    //widget.BarChordVal->setText(active_bar->GetBarChord()); // BUGGED! not editable after set text
    
    // Note editor
    ChangeNoteWidgetFrame(true);
    
    active_bar->update();
}
void Tutor::NoteSelected(Note* note) { // scan Ctrl key pressed for adding second note
    if (!active_note1) {
        active_note1 = note;
        ChangeNoteWidgetFrameAllButAddBtn(true);
    } else if (active_note1 && QApplication::keyboardModifiers() & Qt::ControlModifier) {
        active_note2 = note;
        ChangeNoteWidgetFrameAllButAddBtn(false);
        //widget.NoteContinueVal->setEnabled(true); // TODO additional check if note 1 is last in bar 1; note 2 - first in bar 2
        //widget.NoteSlideVal->setEnabled(true);    // TODO additional check if note 1 and note 2 are in same bar
    } else {
        active_note1 = note;
        ChangeNoteWidgetFrameAllButAddBtn(true);
    }
    active_note1->update();
    if (active_note2) active_note2->update();
    
    if (active_note1 && !active_note2) {
        widget.NoteLengthVal->setValue(64/(int)active_note1->GetBasicLength()); // TODO rename
        widget.NoteExtensionVal->setValue(active_note1->GetExtensionCount());   // TODO rename method!
        widget.NoteVibratoVal->setChecked(active_note1->IsVibrato());
        //widget.NoteGrouppingVal; // TODO
        //widget.NoteUngrouppingVal; // TODO
        widget.NoteContinueVal->setChecked(false);
        widget.NoteSlideVal->setChecked(false);
        ChangeToneWidgetFrame(true);
    } else if (active_note1 && active_note2) {
        widget.NoteLengthVal->setValue(0);    // TODO rename
        widget.NoteExtensionVal->setValue(0); // TODO rename method!
        widget.NoteVibratoVal->setChecked(false);
        widget.NoteGrouppingVal->setValue(0);
        widget.NoteUngrouppingVal->setValue(0);
        if ((active_note1->IsContinuation() && active_note2->IsContinued()) || (active_note2->IsContinuation() && active_note1->IsContinued())) {
            widget.NoteContinueVal->setChecked(true);
        } else {
            widget.NoteContinueVal->setChecked(false);
        }
        if ((active_note1->IsSlide() && active_note2->IsSlided()) || (active_note2->IsSlide() && active_note1->IsSlided())) {
            widget.NoteSlideVal->setChecked(true);
        } else {
            widget.NoteSlideVal->setChecked(false);
        }
        ChangeToneWidgetFrame(false);
    }
    //widget.NoteHORadio; // TODO
    //widget.NotePORadio;
    //widget.NoteHOPOOffRadio;
}

// Play buttons
void Tutor::TrackPlay() {
    
}
void Tutor::BarPlay() {
    
}
void Tutor::NotePlay() {
    
}

void Tutor::StartScholar() {
    if (active_note1) {
        active_note1->SetActive(false);
        active_note1 = NULL;
    }
    if (active_note2) {
        active_note2->SetActive(false);
        active_note2 = NULL;
    }
    if (active_bar) {
        active_bar->SetActive(false);
        active_bar = NULL;
    }
    
    emit PassToScholar(lesson);
    this->hide();
}

void Tutor::FetchFromScholar(Lesson* nlesson) {
    this->show();
    
    if (!nlesson) {
        New();
        return;
    }
    
    if (!lesson) {
        lesson = nlesson;
    } else if (lesson && lesson != nlesson) { // Different pointers (?)
        lesson->DeleteTrack();
        delete lesson;
        lesson = nlesson;
    }
    
    ResizeSceneWidth(1); // Just to align vertically; will be resized on PostPreparation()
    scene->clear();
    std::vector<QGraphicsItem*> visuals = lesson->GetVisualParts();
    for (unsigned i = 0; i < visuals.size(); i++) {
        scene->addItem(visuals.at(i));
    }
    track = lesson->GetTrack();
    
    // Set Editor's active values
    widget.TrackEditFrame->setEnabled(true);
    widget.TrackPlayBtn->setEnabled(true);
    widget.TrackBPMVal->setValue(lesson->GetBPM());
    widget.TrackClefVal->setCurrentIndex( (track->GetClef() == DEFAULT_CLEF ? 0 : 1) );
    widget.TrackBeatCountVal->setValue(track->GetBeatCount());
    widget.TrackBeatLengthVal->setValue(track->GetBeatLength());
    // On NEW Lesson every other component should be turned off
    ChangeBarWidgetFrameAllButAddBtn(false);
    ChangeBarWidgetFrame(true);
}

void Tutor::SubstituteNote(Note* oldN, Note* newN) {
    if (active_note1 == oldN) {
        active_note1 = newN;
        if (Chord *ch = dynamic_cast<Chord*> (active_note1) ) {
            Q_UNUSED(ch);
            AddToneSN_Chord(); // continue note transformation
        }
    }
    if (active_note2 == oldN) {active_note2 = newN;}
    
    scene->removeItem(oldN);
    scene->addItem(newN);
    ResizeSceneWidth(lesson->GetVisualLength());
    SceneUpdate();
}

bool Tutor::eventFilter( QObject * o , QEvent * e )
{
    switch( e->type() )
    {
    case QEvent ::GraphicsSceneMousePress:
        {
            //QGraphicsSceneMouseEvent * event = static_cast< QGraphicsSceneMouseEvent * >( e );
            //qscene->mousePressEvent(event);
            QPoint p = QPoint(widget.TutorMainView->mapFromGlobal(QCursor::pos()));
            QPointF sp = QPointF(widget.TutorMainView->mapToScene(p)); // Needed due to view moving
            QList<QGraphicsItem *> collided_items = scene->items(sp, Qt::IntersectsItemBoundingRect, Qt::AscendingOrder);
            
            if (active_bar) {
                active_bar->SetActive(false);
                active_bar->update();
                active_bar = NULL;
            }
            if (active_note1) { // No check needed?
                if (Chord *ch = dynamic_cast<Chord*> (active_note1) ) {
                    ch->ReleaseCurrSubtone();
                }
                active_note1->SetActive(false);
                active_note1->update();
            }
            if (active_note2) {
                active_note2->SetActive(false);
                active_note2->update();
            }
            active_note1 = active_note2 = NULL;
            if (collided_items.empty()) { // No collision, no advance. TOTO Switch state to paused && return carriage to start
                ChangeBarWidgetFrameAllButAddBtn(false);
                ChangeNoteWidgetFrame(false);
                ChangeNoteWidgetFrameAllButAddBtn(false);
                //ChangeToneWidgetFrame(false);
                //ChangeToneWidgetFrameAllButAddBtn(false);
            } else {
                foreach (QGraphicsItem* item, collided_items) {
                    Note* note = dynamic_cast<Note*>(item);
                    Bar*  bar  = dynamic_cast<Bar*>(item);

                    if (bar) {
                        bar->SetActive(true);
                        BarSelected(bar); // TODO remove signal!
                    }
                    if (note) {
                        note->SetActive(true);
                        if (Chord *ch = dynamic_cast<Chord*> (note) ) {
                            QPointF chp = QPointF(ch->mapFromScene(sp));
                            ch->SetCurrSubtone(chp);
                        }
                        NoteSelected(note); // TODO remove signal!
                    }
                }
                if (!active_note1) {
                    ChangeNoteWidgetFrameAllButAddBtn(false);
                    //ChangeToneWidgetFrame(false);
                    //ChangeToneWidgetFrameAllButAddBtn(false);
                }
                if (!active_bar) {
                    ChangeNoteWidgetFrame(false);
                    ChangeBarWidgetFrameAllButAddBtn(false);
                }
            }
            break;
        }

    case QEvent ::GraphicsSceneMouseRelease:
        {
            break;
        }
    default:
        break;
    }

    return false;
}