/* 
 * File:   Bar.cpp
 * Author: astral
 * 
 * Created on 21 Август 2012 г., 23:43
 */

#include "Bar.h"

static unsigned current_id = 1; // for id buildup

Bar::Bar(unsigned length) {
    id = current_id++;
    if (id == 1){
        repeat_start = true; // permanent!
    } else { 
        repeat_start = false;
    }
     
    repeat_end = 0;
    next_repeat_ending = 0;
    
    this->length = length;
    this->bar_chord = QString("");
    
    next = previous = NULL;
    
    first_note_global_pos = last_note_end_global_pos = QPointF(0, 0);
    //if (id == 1) first_note_global_pos = mapToScene(QPointF(VISUAL_BAR_SPACING, 0)); // A bug for carriage init position
}

Bar::Bar(unsigned length, const char* chord) {
    id = current_id++;
    if (id == 1){
        repeat_start = true; // permanent!
    } else { 
        repeat_start = false;
    }

    repeat_end = 0;
    next_repeat_ending = 0;
    
    this->length = length;
    this->bar_chord = QString(chord);
    
    next = previous = NULL;
}

Bar::Bar(const Bar& orig) {
}

Bar::~Bar() {
    current_id--;
    
    if (next) {
        next->DecreaseId();
    }
}

void Bar::AddNoteBack(Note* note) { notes.push_back(note); }

void Bar::AddNoteAt  (Note* note, unsigned pos) { 
    QVector<Note*>::iterator it = notes.begin();
    for (unsigned i = 0; i < pos; i++, it++);
    notes.insert(it, note); 
}
void Bar::RemoveNoteAt(unsigned pos) {
    QVector<Note*>::iterator it = notes.begin();
    for (unsigned i = 0; i < pos; i++, it++);
    notes.erase(it); 
}

bool Bar::CanBeGrouped(unsigned pos, unsigned n) {
    //TODO
    return false;
}

bool Bar::CanBeUngrouped(unsigned pos, unsigned n) {
    //TODO
    return false;
}

bool Bar::IsLast() const { return id == current_id-1; }

qreal Bar::CalculateVisualBarLength() const { // NB, id bar is red (excess notes are present), bar remain as normal ...
    int i;
    qreal tmplength = 0.;

    for (i = 0; i < notes.size(); i++){
        tmplength += notes.at(i)->GetVisualSizeSpeed().size; // ... otherwise, use GetLength();
    }
    return tmplength;
}

unsigned Bar::CheckBarLength() { // returns actual Note vector length.
    int i, tmplength = 0;

    for (i = 0; i < notes.size(); i++){
        tmplength += notes.at(i)->GetLength();
    }

    return tmplength;
}

void Bar::DecreaseId() { // called on neibour Bar destruction; informs others forward
    id--;
    if (next) {
        next->DecreaseId();
    }
}

void Bar::StichPointers(Bar* previous, Bar* next) {
    if (previous) {
        previous->SetNextBar(this);
    }
    SetPreviousBar(previous);

    if (next) {
        next->SetPreviousBar(this);
    }
    SetNextBar(next);
}

void Bar::ClearNeighbour() { // clear neighbour pointers and stich them toghether
    if (previous) {
        previous->SetNextBar(next);
    }
    if (next) {
        next->SetPreviousBar(previous);
    }
    previous = next = NULL;
}

std::vector<QGraphicsItem*> Bar::GetVisualParts() {
    std::vector<QGraphicsItem*> ret;

    foreach(Note* note, notes) {
        ret.push_back(note);
    }
    
    return ret;
}

qreal Bar::count_bar_length() const {
    qreal bar_len;
    
    bar_len = CalculateVisualBarLength();
    bar_len *= VISUAL_SIZE;                                     // visual size per note ...
    bar_len += NoteCount() * VISUAL_NOTE_SPACING;               // + spacing
    bar_len += 2 * VISUAL_BAR_SPACING;                          // Spacing before and after border
    //if (RepeatEndCount() >= 2) { bar_len += 6; } else           // last bar looks the same
    //if (IsLast()) { bar_len += 6; }
    
    return bar_len;
}

void Bar::DrawTailsSingle(QPainter *painter, Note* note) {
    int dir = (mapFromScene(note->pos()).y() > VISUAL_NOTE_VSPACING*2 ? 1 : -1); // 1 for facing down; VISUAL_NOTE_VSPACING*2 is 3rd line from scene top
    qreal tail_x = (dir == -1 ? mapFromScene(note->scenePos()).x() + note->boundingRect().width() : mapFromScene(note->scenePos()).x()); // tail grows from right or left
    qreal tail_y = mapFromScene(note->pos()).y();
    QPainterPath path;

    painter->setPen(QPen(NOTE_COLOR, 2));
    painter->drawLine(tail_x, tail_y, tail_x, tail_y + dir*AVG_NOTE_TAIL);

    // tails
    
    tail_y = tail_y + dir*AVG_NOTE_TAIL;

// TODO either replace it with arc or recall Bezier materials
#define DRAW_TAIL(K)                                                                                                                        \
do {                                                                                                                                        \
    path.moveTo(tail_x, tail_y - dir*VISUAL_SINGLE_TAIL_VSPACING*(K));                                                                      \
    path.cubicTo(tail_x + VISUAL_SIZE/2, tail_y - dir*(VISUAL_SIZE/2 + VISUAL_SINGLE_TAIL_VSPACING*(K)),                                    \
                    tail_x + VISUAL_SIZE*0.8, tail_y - dir*(VISUAL_SINGLE_TAIL_VSPACING + VISUAL_SINGLE_TAIL_VSPACING*(K)),                 \
                    tail_x + VISUAL_SIZE*0.9, tail_y - dir*(VISUAL_SINGLE_TAIL_VSPACING * 2 + VISUAL_SIZE*0.3 + VISUAL_SINGLE_TAIL_VSPACING*(K)));\
    path.lineTo(tail_x + VISUAL_SIZE*0.8, tail_y - dir*(VISUAL_SINGLE_TAIL_VSPACING * 2 + 0.8 * VISUAL_SIZE * ((K)+1)));                    \
    path.lineTo(tail_x + VISUAL_SIZE*0.9, tail_y - dir*(VISUAL_SINGLE_TAIL_VSPACING * 2 + VISUAL_SIZE*0.3 + VISUAL_SINGLE_TAIL_VSPACING*(K)));\
    painter->drawPath(path);                                                                                                                \
} while(0)
    switch (note->GetBasicLength()) {
        case nl64: // 1 tail per pass through
            //painter->drawRect(tail_x, tail_y + VISUAL_SINGLE_TAIL_VSPACING*3, 5, VISUAL_SINGLE_TAIL_VSPACING*0.5);
            DRAW_TAIL(3);
        case nl32:
            //painter->drawRect(tail_x, tail_y + VISUAL_SINGLE_TAIL_VSPACING*2, 5, VISUAL_SINGLE_TAIL_VSPACING*0.5);
            DRAW_TAIL(2);
        case nl16:
            //painter->drawRect(tail_x, tail_y + VISUAL_SINGLE_TAIL_VSPACING, 5, VISUAL_SINGLE_TAIL_VSPACING*0.5);
            DRAW_TAIL(1);
        case nl8:
            //painter->drawRect(tail_x, tail_y, 5, VISUAL_SINGLE_TAIL_VSPACING*0.5);
            DRAW_TAIL(0);
        default:
            break;
    }
}

bool Point_Y_Comparator(const QPointF &p1, const QPointF &p2)
{
    return p1.y() < p2.y();
}
void Bar::DrawTailsStitched(QPainter* painter, QVector<QPointF>& points, NoteLength active_tail_type) {
    QPointF first, last, topmost, second_top;
    bool side; // true - tails above lines, false - below
    
    first = points.front();
    last = points.back();
    
    // 1st and last pos determinates tails position if both on same vertical side...
    if (first.y() <= VISUAL_NOTE_VSPACING*2 && last.y() <= VISUAL_NOTE_VSPACING*2) {
        side = true;
    } else if (first.y() > VISUAL_NOTE_VSPACING*2 && last.y() > VISUAL_NOTE_VSPACING*2) {
        side = false;
    } else {
        // ... otherwise, side is weighted by all notes
        int weight = 0; // >=0 - above, <0 - below
        foreach(QPointF point, points) {
            weight += (point.y() <= VISUAL_NOTE_VSPACING*2 ? 1 : -1);
        }
        side = weight >= 0;
    }
    
    // Draw tails on right side if going upwards
    if (side) {
        foreach(QPointF point, points) {
            point.setX(point.x() + VISUAL_SIZE); // TODO WTF??? it doesn't change anything
        }
        first.setX(first.x() + VISUAL_SIZE);
        last.setX(last.x() + VISUAL_SIZE);
    }
    
    assert(points.size() >= 2);
    qSort(points.begin(), points.end(), Point_Y_Comparator);
    topmost = points[0];
    second_top = points[1];
    if (side) {
        foreach(QPointF point, points) {                                                // Find top note
            if (point.y() < topmost.y()) { second_top = topmost; topmost = point; }     // NB y scales down
        }
    } else {
        foreach(QPointF point, points) {                                                // Or bottom one
            if (point.y() > topmost.y()) { second_top = topmost; topmost = point; }
        }
    }
    
    // Close tail inside bounding rect
    topmost.setY(topmost.y() + (side ? -AVG_NOTE_TAIL : AVG_NOTE_TAIL));
    if (side && topmost.y() < -VISUAL_NOTE_VSPACING*4) { topmost.setY(-VISUAL_NOTE_VSPACING*4); }               // Line by bar's top
    else if (!side && topmost.y() > 2*VISUAL_NOTE_VSPACING*4) { topmost.setY(2*VISUAL_NOTE_VSPACING*4); }       // Line by bar's bottom
    second_top.setY(second_top.y() + (side ? -AVG_NOTE_TAIL : AVG_NOTE_TAIL));
    // Reduce angle
    if (side && topmost.y() - second_top.y() < -AVG_NOTE_TAIL/2) { second_top.setY(topmost.y() + AVG_NOTE_TAIL/2); }
    else if (!side && topmost.y() - second_top.y() > AVG_NOTE_TAIL/2) { second_top.setY(topmost.y() - AVG_NOTE_TAIL/2); }
    
    // Extrapolate points to firts and last notes
    qreal k = (topmost.y() - second_top.y())/(topmost.x() - second_top.x());
    qreal b = topmost.y() - k*topmost.x();
    first.setY(first.x()*k + b);
    last.setY(last.x()*k + b);
    //QLineF base_line = QLineF(topmost, second_top);
    
    // Connect note bases to tail
    painter->setPen(QPen(NOTE_COLOR, 2));
    if (side) { // This part shuldn't be here! But setX for every point did NOT work (?)
        foreach(QPointF point, points) {
            painter->drawLine(point.x() + VISUAL_SIZE, point.y(), point.x() + VISUAL_SIZE, (point.x()+VISUAL_SIZE)*k + b);
        }
    } else
    foreach(QPointF point, points) {
        painter->drawLine(point.x(), point.y(), point.x(), point.x()*k + b);
    }
    
    // Tail stitching
    QPointF spacing = QPointF(0, 2*VISUAL_SINGLE_TAIL_VSPACING);
    painter->setPen(QPen(NOTE_COLOR, 3)); // Thicken the line
    switch (active_tail_type) {
        case nl64: // 1 tail per pass through
            painter->drawLine(first + 3*(side ? spacing : -spacing), last + 3*(side ? spacing : -spacing));
        case nl32:
            painter->drawLine(first + 2*(side ? spacing : -spacing), last + 2*(side ? spacing : -spacing));
        case nl16:
            painter->drawLine(first + 1*(side ? spacing : -spacing), last + 1*(side ? spacing : -spacing));
        case nl8:
            painter->drawLine(first, last);
        default:
            break;   
    }
}

void Bar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    qreal bar_len;
    qreal line1Y = 0;
    qreal line2Y = line1Y + VISUAL_NOTE_VSPACING;
    qreal line3Y = line2Y + VISUAL_NOTE_VSPACING;
    qreal line4Y = line3Y + VISUAL_NOTE_VSPACING;
    qreal line5Y = line4Y + VISUAL_NOTE_VSPACING;
    QFont f;

    // Test
    //painter->drawRect(boundingRect());
    
    // Bar color
    int bar_avalable_space = CheckAvalableSpace();
    if (!bar_avalable_space) {
        color = QColor(NORMAL_COLOR);       // Bar is exact size
    } else if (bar_avalable_space > 0) {
        color = QColor(INCOMPLETE_COLOR);   // Bar space is avalable
    } else {
        color = QColor(EXCESS_COLOR);       // Bar's notes are in excess and some of them must must to be removed
    }
    painter->setBrush(color);
    painter->setPen(QPen(color, 2));

    // Lines
    bar_len = count_bar_length();
    painter->drawLine(0, line1Y, bar_len, line1Y);
    painter->drawLine(0, line2Y, bar_len, line2Y);
    painter->drawLine(0, line3Y, bar_len, line3Y);
    painter->drawLine(0, line4Y, bar_len, line4Y);
    painter->drawLine(0, line5Y, bar_len, line5Y);

    // Bar chord name
    f = QFont("Times New Roman");
    f.setPixelSize(VISUAL_NOTE_VSPACING*1.2);
    painter->setFont(f);
    painter->drawText(VISUAL_NOTE_SPACING/3, -VISUAL_NOTE_VSPACING, GetBarChord());

    // Repeat endings (over bar arc)
    static unsigned bar_repeat_number = 0;          // Visual number
    static unsigned bar_repeat_counter_tmp = 0;     // temp variable
    static unsigned next_repeat_id = 0;             // id
    if ( (next_repeat_id = GetNextRepeatEndingId()) && (bar_repeat_counter_tmp = RepeatEndCount()) > 2 ) { // Abnormal state as endings may be only 2 (? Atleast Sposobin's book says so)
        painter->drawLine(0, -VISUAL_NOTE_VSPACING*2, 0, -VISUAL_NOTE_VSPACING*4); // TODO make private f() with arguments: painter and QString
        painter->drawLine(0, -VISUAL_NOTE_VSPACING*4, bar_len - 2, -VISUAL_NOTE_VSPACING*4);
        painter->drawText(VISUAL_NOTE_SPACING, -VISUAL_NOTE_VSPACING*2, "???");
    } else if ( bar_repeat_counter_tmp == 2 && next_repeat_id && !bar_repeat_number) {                                  // 1. ending
        bar_repeat_number = 1;
        painter->drawLine(0, -VISUAL_NOTE_VSPACING*2, 0, -VISUAL_NOTE_VSPACING*4);
        painter->drawLine(0, -VISUAL_NOTE_VSPACING*4, bar_len - 2, -VISUAL_NOTE_VSPACING*4);
        painter->drawText(VISUAL_NOTE_SPACING, -VISUAL_NOTE_VSPACING*2, QString::number(bar_repeat_number++));
    } else if (bar_repeat_number == 2) {                                                                                // 2. ending
        painter->drawLine(0, -VISUAL_NOTE_VSPACING*2, 0, -VISUAL_NOTE_VSPACING*4);
        painter->drawLine(0, -VISUAL_NOTE_VSPACING*4, bar_len - 2, -VISUAL_NOTE_VSPACING*4);
        painter->drawText(VISUAL_NOTE_SPACING, -VISUAL_NOTE_VSPACING*2, QString::number(bar_repeat_number));
        bar_repeat_number = 0; // clear endings
    }

    // [OPTIONAL] Dotted vertival lines (---) to see acrual borders
    // if (options->dotted_borders) // TODO
    // painter->setPen(Qt::DashLine);
    //painter->drawLine(0 + VISUAL_BAR_SPACING, line1Y - VISUAL_NOTE_VSPACING * 4, 0 + VISUAL_BAR_SPACING, line5Y + VISUAL_NOTE_VSPACING * 4);
    //painter->drawLine(0 + bar_len - VISUAL_BAR_SPACING, line1Y - VISUAL_NOTE_VSPACING * 4, 0 + bar_len - VISUAL_BAR_SPACING, line5Y + VISUAL_NOTE_VSPACING * 4);

    // Notes
    SingleNote* sn = NULL;
    //Chord* ch = NULL;
    QPointF note_point = mapToScene(QPointF(VISUAL_BAR_SPACING, 0));  // TODO Replace this and mapFromScene with normal coords and note->setPos(note_point); to mapToScene
    QVector<QPointF> tails;            // note vector to stitch tails.
    NoteLength active_tail_type = nl1; // Defines tail line type and count (on type change). Draw tail groupping if type <= nl8 and tails.count() > 1
    painter->setPen(QPen(NOTE_COLOR, 2)); // solid fill from now on
    foreach(Note* note, notes) {
        VisualSizeSpeed vss;
        
        // Note basics
        vss = note->GetVisualSizeSpeed();
        note->setPos(note_point);
        if (sn = dynamic_cast<SingleNote*>(note)) {  
            if (sn->GetPitch()) { sn->AdjustNote(note_point.toPoint(), clef); }
            else {sn->setPos(note_point.x(), mapToScene(QPointF(0, line2Y)).y()); } // TODO make it simplier!
        //} else if (Chord* ch = dynamic_cast<Chord*>(note)) {
        //    (void*)ch; // TODO
        }
        
        // Rests
        // TODO recursive implementation for extensions (?)
        if (sn && sn->GetPitch() == 0) {
            QImage rest4, rest8, rest16, rest32, rest64;
            rest4.load(":/images/4th.png");
            rest8.load(":/images/8th.png");
            rest16.load(":/images/16th.png");
            rest32.load(":/images/32th.png");
            rest64.load(":/images/64th.png");
            
            if(tails.size() > 1) {                 // Flush tail stitching before rest
                DrawTailsStitched(painter, tails, active_tail_type);
                tails.clear();
            }
            
            painter->setBrush(NOTE_COLOR); // solid
            painter->setPen(QPen(NOTE_COLOR, 0));
            switch (note->GetBasicLength()) {
                case nl1:
                    painter->drawRect(mapFromScene(note_point).x(), line2Y, VISUAL_SIZE, VISUAL_NOTE_VSPACING/2);
                    break;
                case nl2:
                    //painter->drawRect(boundingRect().x(), boundingRect().y() + boundingRect().height()/2, boundingRect().x() + boundingRect().width(), boundingRect().y() + boundingRect().height());
                    painter->drawRect(mapFromScene(note_point).x(), line3Y, VISUAL_SIZE, -VISUAL_NOTE_VSPACING/2);
                    break;
                case nl4:
                    painter->drawImage(QRectF(mapFromScene(note_point).x(), line1Y+VISUAL_NOTE_VSPACING/2, 1.5*VISUAL_SIZE, 3*VISUAL_NOTE_VSPACING), rest4);
                    break;
                case nl8:
                    painter->drawImage(QRectF(mapFromScene(note_point).x(), line2Y, 1.5*VISUAL_SIZE, 2*VISUAL_NOTE_VSPACING), rest8);
                    break;
                case nl16:
                    painter->drawImage(QRectF(mapFromScene(note_point).x(), line2Y, 1.8*VISUAL_SIZE, 3*VISUAL_NOTE_VSPACING), rest16);
                    break;
                case nl32:
                    painter->drawImage(QRectF(mapFromScene(note_point).x(), line1Y, 2*VISUAL_SIZE, 4*VISUAL_NOTE_VSPACING), rest32);
                    break;
                case nl64:
                    painter->drawImage(QRectF(mapFromScene(note_point).x(), line1Y, 2.5*VISUAL_SIZE, 5*VISUAL_NOTE_VSPACING), rest64);
                    break;
                default:
                    break;
            }
            note_point.setX(note_point.x() + VISUAL_NOTE_SPACING + vss.size * VISUAL_SIZE );
            continue; // ignore helpers (drawn in the middle) and tails
        }
        
        // Line helpers
        QPointF n_pos = mapFromScene(note->pos());
        painter->setBrush(color);
        painter->setPen(QPen(color, 2));
        if (n_pos.y() > line5Y){
            for (qreal y = (fmod(n_pos.y(), VISUAL_NOTE_VSPACING) == 0 ? n_pos.y() : n_pos.y() + VISUAL_NOTE_VSPACING*0.5); y > line5Y; y -= VISUAL_NOTE_VSPACING){ // Align extra lines for notes like B, D, etc
                painter->drawLine(n_pos.x() - VISUAL_SIZE, y, n_pos.x() + VISUAL_SIZE*2, y);
            }
        } else if (n_pos.y() < line1Y) {
            for (qreal y = (fmod(n_pos.y(), VISUAL_NOTE_VSPACING) == 0 ? n_pos.y() : n_pos.y() - VISUAL_NOTE_VSPACING*0.5); y >= line5Y; y += VISUAL_NOTE_VSPACING){
                painter->drawLine(n_pos.x() - VISUAL_SIZE, y, n_pos.x() + VISUAL_SIZE*2, y);
            }
        }
        
        // Tails
        if (note->GetBasicLength() <= nl2) {     // Draw atleast vertical line
            
            if (note->GetBasicLength() <= nl8) { // Advanced tail drawing
                if (active_tail_type == note->GetBasicLength() && note->GetExtensionCount() == 0) {
                    tails.push_back(mapFromScene(note->pos())); // NB adding mostleft point of note; coordinates mapped to Bar
                } else if(tails.size() > 1) {                 // Flush tail stitching
                    DrawTailsStitched(painter, tails, active_tail_type);
                    tails.clear();
                    
                    // currnet note length is nor repeated on next one; ignore '.'
                    if (notes.indexOf(note)+1 == notes.size() || notes.at(notes.indexOf(note) + 1)->GetBasicLength() != note->GetBasicLength() || note->GetExtensionCount() > 0) {
                        DrawTailsSingle(painter, note);
                        active_tail_type = nl1;
                    } else { // New group
                        tails.push_back(mapFromScene(note_point)); // Stich group later
                        active_tail_type = note->GetBasicLength();
                    }
                } else { // incl tails.count()==1 ???
                    // currnet note length is nor repeated on next one
                    if (notes.indexOf(note)+1 == notes.size() || notes.at(notes.indexOf(note) + 1)->GetBasicLength() != note->GetBasicLength() || note->GetExtensionCount() > 0) {
                        DrawTailsSingle(painter, note);
                        active_tail_type = nl1;
                    } else {
                        tails.push_back(mapFromScene(note->pos())); // 1-st occurance of group; Stich group later
                        active_tail_type = note->GetBasicLength();
                    }
                }
            } else {                             // Only vertical line for nl2 and nl4
                int dir = (mapFromScene(note->pos()).y() > line3Y ? 1 : -1); // +1 for facing down
                qreal tail_x = (dir == -1 ? mapFromScene(note_point).x() + note->boundingRect().width() : mapFromScene(note_point).x()); // tail grows from right or left
                qreal tail_y = mapFromScene(note->pos()).y();
                painter->setPen(QPen(NOTE_COLOR, 2)); // Let it be here, as tail stitching changes thicknes
                painter->drawLine(tail_x, tail_y, tail_x, tail_y + dir*AVG_NOTE_TAIL);
                
                if(tails.size() > 1) {                 // Flush tail stitching on nl1, 2 nad 4
                    DrawTailsStitched(painter, tails, active_tail_type);
                    tails.clear();
                }
            }
        } else {
            if(tails.size() > 1) {                 // Flush tail stitching on nl1, 2 nad 4
                DrawTailsStitched(painter, tails, active_tail_type);
                tails.clear();
            }
        }
        
        // Next note
        note_point.setX(note_point.x() + VISUAL_NOTE_SPACING + vss.size * VISUAL_SIZE );
    }
    if(tails.size() > 1) {                 // Flush tail stitching on bar end
        DrawTailsStitched(painter, tails, active_tail_type);
        tails.clear();
    }
    note_point.setX(bar_len);

    // ***
    // Borders
    //
    // Repeat signs
    int repeat_count;
    painter->setBrush(color);
    painter->setPen(QPen(color, 2));
    // Repeat start
    if (id > 1 && repeat_start) {
        painter->drawRect(0, 0, 3, VISUAL_NOTE_VSPACING * 4);
        painter->drawRect(6, 0, 1, VISUAL_NOTE_VSPACING * 4);
        painter->drawEllipse(QPointF(12, VISUAL_NOTE_VSPACING*1.5), 1.5, 1.5);
        painter->drawEllipse(QPointF(12, VISUAL_NOTE_VSPACING + VISUAL_NOTE_VSPACING*1.5), 1.5, 1.5);
    }
    // Repeat end
    if ((repeat_count = RepeatEndCount()) >= 2) {
        painter->drawEllipse(QPointF(note_point.x() - 12, VISUAL_NOTE_VSPACING*1.5), 1.5, 1.5);
        painter->drawEllipse(QPointF(note_point.x() - 12, VISUAL_NOTE_VSPACING + VISUAL_NOTE_VSPACING*1.5), 1.5, 1.5);
        painter->drawRect(note_point.x() - 8, 0, 1, VISUAL_NOTE_VSPACING * 4);
        painter->drawRect(note_point.x() - 4, 0, 3, VISUAL_NOTE_VSPACING * 4);
        if (repeat_count > 2) painter->drawText(note_point.x() - 8, -VISUAL_NOTE_VSPACING/2, QString::number(repeat_count));
        //draw_pos.setX(0 + 10);
    } else // last bar looks the same, only w/o/ dots
    // Last bar
    if (IsLast()) {
        // Ending itself
        painter->drawRect(note_point.x() - 7, 0, 1, VISUAL_NOTE_VSPACING * 4);
        painter->drawRect(note_point.x() - 3, 0, 3, VISUAL_NOTE_VSPACING * 4);
        //draw_pos.setX(0 + 6);

        bar_repeat_number = next_repeat_id = 0; // clear loop
    } else {
    //Ordinary border
        painter->drawRect(note_point.x()-1, 0, 1, VISUAL_NOTE_VSPACING * 4);
    }
    
    // Gray parts (where notes are not affected, just visual spacin inside bars)
    first_note_global_pos = mapToScene(QPointF(VISUAL_BAR_SPACING, 0));
    last_note_end_global_pos = mapToScene(QPointF(note_point.x() - (VISUAL_BAR_SPACING + (RepeatEndCount() >= 2 || IsLast() ? 6 : 0)), 0));
    // if (options->gray_bar_borders) // TODO
    color = QColor(GRAY_BORDER_COLOR);
    painter->setBrush(color);
    painter->setPen(QPen(color, 0));
    painter->setBrush(Qt::Dense6Pattern);
    painter->drawRect(0, 0, VISUAL_BAR_SPACING, VISUAL_NOTE_VSPACING * 4);
    //painter->drawRect(note_point.x() - (VISUAL_BAR_SPACING + (RepeatEndCount() >= 2 || IsLast() ? 6 : 0)), 0, VISUAL_BAR_SPACING, VISUAL_NOTE_VSPACING * 4);
    painter->drawRect(note_point.x() - VISUAL_BAR_SPACING, 0, VISUAL_BAR_SPACING, VISUAL_NOTE_VSPACING * 4);
}