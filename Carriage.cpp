/* 
 * File:   Carriage.cpp
 * Author: astral
 * 
 * Created on 19 Сентябрь 2012 г., 22:41
 */

#include <iostream>

#include "Carriage.h"
#include "Bar.h"

//qreal timeout;

Carriage::Carriage(QObject* parent, unsigned bpm) : QObject(parent) {
    this->bpm = bpm;
    visual_speed = 1;    //start speed
    active_note = NULL;
    play_state = false;
    back_from_pause = false;
    etalon = nl4;

    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(ClearTimer()));
    timer.setSingleShot(true);
    time.start();
}

Carriage::Carriage(const Carriage& orig) {
}

Carriage::~Carriage() {
    repeat_start.clear();
    repeat_border.clear();
    repeat_count.clear();
    repeat_border_ignore.clear();
    repeat_start_ignore = NULL;
    next_bar_repeat_1 = NULL;
}

void Carriage::SetState (bool state) {
    if (!play_state && state) { back_from_pause = true; }
    play_state = state; 
    time.restart();
}

void Carriage::ClearTimer() {  
    timer.stop();
    active_note = NULL;
    // Test
    //scene()->addLine(mapToScene(boundingRect()).boundingRect().x(), -10, mapToScene(boundingRect()).boundingRect().x(), 160);
}

void Carriage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush(QColor(CARRIAGE_COLOR));
    painter->setPen(QPen(QColor(CARRIAGE_COLOR), 2));
    //painter->drawRect(boundingRect()); // (Bug) Pulsing on advance
    
    // TODO allow to turn off by options
    painter->drawLine(boundingRect().x(), boundingRect().y(), boundingRect().x() + boundingRect().width(), boundingRect().y() + boundingRect().height());
}

void Carriage::advance(int step)
 {
    static int ta = 0;                    // timer adjustment: Windows precision is about 15ms, so it either 15 or 30, when we need i.e. 21
    static const qreal CA = 60000.0/TICS; // Adjustment constant
    static qreal adjusted_to_timer = 1;   // Timer adjustment coefficient
    
    if (!play_state) return;   // Playback stopped; must be before if (!step) to NOT to trigger ta=time.restart();
    
    if (!step) {
        ta=time.restart(); // On prep. state t/o > 0; on next cycle: step = 1, t/o = 0
        return;            // Ignore preparation state
    }

    QList<QGraphicsItem *> collided_items = scene()->collidingItems(this, Qt::IntersectsItemBoundingRect);
    if (collided_items.empty()) { // No collision, no advance. TOTO Switch state to paused && return carriage to start
        play_state = false;
        emit Finished();
        ta = 0;
        repeat_start.clear();
        repeat_border.clear();
        repeat_count.clear();
        repeat_border_ignore.clear();
        repeat_start_ignore = NULL;
        return;
    }
    
    static const VisualSizeSpeed nl4_etalon_vss = GlobalGetVisualSizeSpeed(etalon, 0);                // TODO get etalon from track/lesson
    static const qreal C1 = ((VISUAL_NOTE_SPACING*nl4_etalon_vss.size)/(TICS*nl4_etalon_vss.speed))/CA; // constants for carriage speed
    static const qreal C2 = ((VISUAL_SIZE*nl4_etalon_vss.size)/(TICS*nl4_etalon_vss.speed))/CA;
    static qreal v_est = visual_speed/CA;               // Must be x/CA on init due to X*ta*bpm    // Estimated speed (before timer lag adjustment): note speed * note length per 1 TICK
    
    foreach (QGraphicsItem* item, collided_items) {
        VisualSizeSpeed vss;
        Note* note = dynamic_cast<Note*>(item);
        Bar*  bar  = dynamic_cast<Bar*>(item);
        if (back_from_pause) {
            if (note) continue; // Do not fetch new data
            else back_from_pause = false; // Clear flag
        }
        if (bar) { // TODO optimize this part
            // Add repeat start
            if ( (bar->GetId() == 1 && repeat_start.isEmpty()) || 
                 (bar->IsRepeatStart() && (repeat_start.isEmpty() || repeat_start.top() != bar) && repeat_start_ignore != bar)) { // Top assumes that isEmpty is checked
                repeat_start.push(bar);
                repeat_start_ignore = NULL;
                next_bar_repeat_1 = NULL;
                // Test
                //scene()->addLine(mapToScene(boundingRect()).boundingRect().x(), -10, mapToScene(boundingRect()).boundingRect().x(), 160);
            }
            // Add repeat border
            if ( (bar->RepeatEndCount() >= 2 && (repeat_border.isEmpty() || repeat_border.top() != bar) && repeat_border_ignore.indexOf(bar) == -1) ) {
                repeat_border.push(bar);
                repeat_count.push(bar->RepeatEndCount());
                if (bar->GetNextBar() && bar->GetNextRepeatEndingId() == bar->GetNextBar()->GetId()) {
                    next_bar_repeat_1 = bar;
                }
                
                // Clear previous ignores and prevent current bar from adding to repeat_border (untill outer repeat is found).
                if (!repeat_border_ignore.isEmpty() && repeat_border_ignore.top()->GetId() < bar->GetId()) {
                    while (!repeat_border_ignore.isEmpty() && repeat_border_ignore.top()->GetId() < bar->GetId()) {
                        repeat_border_ignore.pop();
                    }
                }
                repeat_border_ignore.push(bar);
            }
            
            // Passed all notes and on gray area; HOPE that on 240 BPM and 1/64 it won't pass onto next bar
            if (!active_note && this->scenePos().x() > bar->GetPastLastNotePos().x()) {//bar->GrayAreaIntersection(this->scenePos())) {
                Bar* next_bar = NULL;
                if (!repeat_border.isEmpty() && repeat_border.top() == bar) {
                    if (repeat_border.top() == repeat_start.top() && next_bar_repeat_1 && next_bar_repeat_1 == bar) { // if repeat ending 1. starts and ends on same bar
                        next_bar = next_bar_repeat_1->GetNextBar();                     // jump to repeat_ending 2.
                    } else {
                        next_bar = repeat_start.top(); // TODO add next_repeat_ending
                    }
                    if (--repeat_count.top() <= 1) {
                        repeat_count.pop();
                        repeat_border.pop();
                        if (repeat_start.top()->GetId() != 1) { // 1-st bar is always repeatable; repeat_start_ignore removes curr bar infinite looping
                            repeat_start_ignore = repeat_start.pop();
                        } else {
                            repeat_start_ignore = NULL; // On rewinding to 1-st ball, every repeaters becomes active again;
                            next_bar_repeat_1 = NULL;
                        }
                    }
                } else if (!bar->IsLast()) {
                    if (next_bar_repeat_1 && next_bar_repeat_1 == bar->GetNextBar()) {
                        next_bar = next_bar_repeat_1->GetNextBar();                     // jump to repeat_ending 2.
                        next_bar_repeat_1 = NULL;
                    } else {
                        next_bar = bar->GetNextBar();
                    }
                }
                if (next_bar) { setPos(next_bar->GetFirstNotePos()); }
                // else {} // Else let it pass through and emit Finished();
                continue;
            } else if ( !active_note && this->scenePos().x() < bar->GetFirstNotePos().x() ) { // Carriage is on next bar or (most probably) on Lesson start; advance to 1-st note
                setPos(bar->GetFirstNotePos());
                continue;
            }
        }
        if (!note) {
            continue;           // Fetch only notes
        }
        if (active_note && active_note == note) continue; // TODO add exception, as active_note shoult be disposed by timeout
        active_note = note;
        if (timer.isActive()) {timer.stop(); // Clear timer due to out-of sync problem (up to 11 ms)
                //TEST Dispose 2 lines below
                //scene()->addLine(mapToScene(boundingRect()).boundingRect().x(), -10, mapToScene(boundingRect()).boundingRect().x(), 160);
                //std::cout << "Time elapsed: " << time.elapsed() << "; delta: " << time.elapsed()-timeout << "\n";
        }
                
        if (back_from_pause) {
            if (note) continue;           // Do not fetch new data
            else back_from_pause = false; // Clear flag
        }
        
        vss = note->GetVisualSizeSpeed();
        v_est = vss.speed*(C1/vss.size + C2);
        /* Formula above is optimized version of calculations below */
        //qreal px_per_note = (VISUAL_NOTE_SPACING + VISUAL_SIZE*vss.size);
        //qreal px_per_beat = px_per_note / (vss.size/nl4_etalon_vss.size); // 1 beat = etalon = usualy 1/4 
        ///*qreal*/ v_est = (vss.speed/nl4_etalon_vss.speed)*px_per_beat;
        /* Oroginal formula */
        //visual_speed = (vss.speed/nl4_etalon_vss.speed)*(VISUAL_NOTE_SPACING + VISUAL_SIZE*vss.size)/(TICS*vss.size/nl4_etalon_vss.size);
        if (!timer.isActive()) {
            qreal timeout = (60000.0/bpm) * ((qreal)note->GetLength()/nl4); //TODO use Continued flad to extent timeout till next bar;
            emit PassNote(note);
            timer.start( floor(timeout + 0.5) ); // 1 beat (1/4) to note's proportion; 935 instead of 1K msecs 'couse of interrupts???
            //std::cout << "Timeout: " << timeout << "; ";
            //time.restart();
        }
    }
    
    adjusted_to_timer = ta*bpm;
    //visual_speed =  v_est*adjusted_to_timer/TICS; Replaced by optimized formula
    visual_speed =  v_est*adjusted_to_timer;
    setPos(mapToParent(visual_speed, 0));
}
