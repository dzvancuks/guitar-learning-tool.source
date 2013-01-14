/* 
 * File:   LoadStore.cpp
 * Author: astral
 * 
 * Created on 20 Октябрь 2012 г., 14:44
 */

#include "LoadStore.h"

 // [IN] Lesson *lesson, [IN] QFile *file
void LoadStore::Store(Lesson *lesson, QFile *file) {
    if (!lesson || !file) return;
    
    //GOOGLE_PROTOBUF_VERIFY_VERSION;

    LessonFile lessonf;
    lessonf.set_creator(getenv("USERNAME"));
    
    LessonFile_Lesson lf_lesson;
    lf_lesson.set_bpm(lesson->GetBPM());
    
    LessonFile_Track lf_track;
    lf_track.set_beat_count(lesson->GetTrack()->GetBeatCount());
    lf_track.set_beat_length(lesson->GetTrack()->GetBeatLength());
    if (lesson->GetTrack()->GetClef() == treble) {
        lf_track.set_clef(LessonFile_ClefType_treble);
    } else {
        lf_track.set_clef(LessonFile_ClefType_bass);
    }
    foreach(Bar *bar, lesson->GetTrack()->GetBars()) {
        LessonFile_Bar *lf_bar = lf_track.add_bars();
        lf_bar->set_id(bar->GetId());
        lf_bar->set_length(bar->GetLength());
        lf_bar->set_repeat_start(bar->IsRepeatStart());
        lf_bar->set_repeat_end(bar->RepeatEndCount());
        lf_bar->set_next_repeat_ending(bar->GetNextRepeatEndingId());
        lf_bar->set_bar_chord(bar->GetBarChord().toStdString());
        
        foreach(Note *note, bar->GetNotes()) {
            LessonFile_Note *lf_note = lf_bar->add_notes();
            lf_note->set_length((LessonFile_NoteLength)note->GetBasicLength()); // TODO Note's method will be renamed!
            lf_note->set_extension(note->GetExtensionCount());
            lf_note->set_continueto(note->IsContinuation()); // On load linked like this: on every continueTo, next continuedFrom makes pointer connection
            lf_note->set_continuedfrom(note->IsContinued());
            lf_note->set_slideto(note->IsSlide());           // Same as above
            lf_note->set_slidedfrom(note->IsSlided());
            lf_note->set_vibrato(note->IsVibrato());
            lf_note->set_ho(note->IsHO());
            lf_note->set_po(note->IsPO());
            lf_note->set_grouping(note->GetGrouping());
            lf_note->set_ungrouping(note->GetUngrouping());
            lf_note->set_in_group(note->GetInGroup()); // Can be omitted?
            
            SingleNote *sn;
            Chord *ch;
            if ( (sn = dynamic_cast<SingleNote*> (note)) ) {
                LessonFile_Tone *lf_tone = lf_note->add_tone();
                lf_tone->set_pitch(sn->GetPitch());
                lf_tone->set_str(sn->GetString());
            } else if ( (ch = dynamic_cast<Chord*> (note)) ) { 
                for(int i = 0; i < ch->GetChord().size(); i++) {
                    Subnote *tone = ch->GetChord().at(i);
                    LessonFile_Tone *lf_tone = lf_note->add_tone();
                    lf_tone->set_pitch(tone->tone);
                    lf_tone->set_str(tone->string);
                }
            }
        }
    }
    lf_lesson.mutable_track()->CopyFrom(lf_track);
    
    lessonf.mutable_lesson()->CopyFrom(lf_lesson);
    
    // lessonf.set_signature(hash_from_lesson + creator's name)
    
    //QString str;
    //std::string *str = new std::string();
    int size = lessonf.ByteSize();
    char* data = new char[size];
    lessonf.SerializeToArray(data, size);
    file->write(data, size);
    //google::protobuf::ShutdownProtobufLibrary();
}

// [OUT] Lesson *lesson, [IN] QFile *file
void LoadStore::Load(Lesson **dp_lesson, QFile *file) {
    if (!file) return;
    
    char data[MAX64K];
    int size;
    //std::string *str;
    LessonFile lessonf;
    //LessonFile_Lesson lf_lesson;
    
    if ((size = file->read(data, MAX64K)) == -1) return;
    //str = new std::string(data, read);
    //data = new char[size];
    
    lessonf.ParseFromArray(data, size);
    
    Lesson *lesson = *dp_lesson;
    if (!lesson) {
        lesson = new Lesson();
        *dp_lesson = lesson;
    } else {
        lesson->DeleteTrack();
    }
    
    lesson->SetBPM(lessonf.lesson().bpm());
    
    LessonFile_Track lf_track = lessonf.lesson().track();
    Track *track = new Track(
            (lf_track.clef() == LessonFile_ClefType_treble ? treble : bass),
            lf_track.beat_count(), lf_track.beat_length()
            );
    
    QStack<Note*> slide_start; // popped on every "slided" flag and both flags for both notes are set
    QStack<Note*> continue_start; // popped on every "continued" flag and both flags for both notes are set
    for (int i = 0; i < lf_track.bars_size(); i++) {
        LessonFile_Bar lf_bar = lf_track.bars(i);
        Bar *bar = new Bar(lf_bar.length());
        bar->SetRepeatStart(lf_bar.repeat_start());
        bar->SetRepeatEnd(lf_bar.repeat_end());
        bar->SetNextRepeatEndingId(lf_bar.next_repeat_ending()); // Should be safe. Or at least "???" will be drawn
        bar->SetBarChord(QString::fromStdString(lf_bar.bar_chord()));
        
        
        for (int j = 0; j < lf_bar.notes_size(); j++) {
            LessonFile_Note lf_note = lf_bar.notes(j);
            Note *note; // = new Note();
            if (lf_note.tone_size() == 1) {
                note = new SingleNote((NoteLength)lf_note.length(), (unsigned)lf_note.extension());
            } else {
                std::vector<double> dummy = std::vector<double>();
                note = new Chord(dummy, (NoteLength)lf_note.length(), lf_note.extension()); // TODO
            }
            
            // Continue flags, NB try to check "continued" flag first, as one note can be continued in several bars!
            if (lf_note.continuedfrom()) {
                if (continue_start.size()) {
                    continue_start.top()->SetContinuation(note);
                    note->SetContinued(continue_start.top());
                    continue_start.pop();
                } // else {throw exception} // TODO
            }
            if (lf_note.continueto()) {
                continue_start.push(note); // Will be stitched later
            }
            // Slide flags
            if (lf_note.slidedfrom()) {
                if (slide_start.size()) {
                    slide_start.top()->SetSlide(note);
                    note->SetSlided(slide_start.top());
                    slide_start.pop();
                } // else {throw exception} // TODO
            }
            if (lf_note.slideto()) {
                slide_start.push(note); // Will be stitched later
            }
            
            if (lf_note.vibrato()) note->SetVibrato();
            if (lf_note.ho()) note->SetHO();
            if (lf_note.po()) note->SetPO();
            
            note->SetGrouping(lf_note.grouping());
            note->SetUngrouping(lf_note.ungrouping());
            note->SetInGroup(lf_note.in_group());
            
            if (lf_note.tone_size() == 1) {
                SingleNote *sn = dynamic_cast<SingleNote*> (note);
                sn->SetPitch(lf_note.tone(0).pitch());
                sn->SetString(lf_note.tone(0).str());
            }  else {
                Chord *ch = dynamic_cast<Chord*> (note);
                for(int i = 0; i < lf_note.tone_size(); i++) {
                    LessonFile_Tone t = lf_note.tone(i);
                    Subnote s;
                    s.octave_notes_pos = 0; // will be adjusted by Chord class
                    s.tone = t.pitch();
                    s.string = t.str();
                    ch->AddTone(s);
                }
            }
            
            bar->AddNoteBack(note);
        }
        
        track->AddBarBack(bar);
    }
    
    lesson->SetTrack(track);
}
