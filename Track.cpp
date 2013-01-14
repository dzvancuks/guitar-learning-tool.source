/* 
 * File:   Track.cpp
 * Author: astral
 * 
 * Created on 22 Август 2012 г., 21:40
 */

#include "Track.h"



Track::Track(ClefType clef, unsigned beat_count, unsigned beat_length) {
    this->clef = clef;
    this->beat_count = beat_count;
    
    /* Use KISS instead :)
    unsigned int nlBitCount; //check on bit count; thank guys from http://tekpool.wordpress.com/category/bit-count/
    nlBitCount = beat_length - ((beat_length >> 1) & 033333333333) - ((beat_length >> 2) & 011111111111);
    nlBitCount = ((nlBitCount + (nlBitCount >> 3)) & 030707070707) % 63;
    */
    unsigned int bit_count = 0, tbeat_length = beat_length;
    while (tbeat_length) {
        bit_count = tbeat_length & 0x1;
        tbeat_length >>= 1;
    }
    
    assert(bit_count == 1 && beat_length > 0 && beat_length <= nl1); //(NoteLength & ((nl1 << 1) - 1) ));
    this->beat_length = beat_length;
    
    bpos.setX(0);
    bpos.setY(50);
    spacing = VISUAL_NOTE_VSPACING;
    clef_w = 100; // TODO Adjust
    //color = QColor(NORMAL_COLOR);
}

Track::Track(const Track& orig) {
}

Track::~Track() {
}

void Track::SetClef(ClefType clef) { 
    this->clef = clef;
    if (bars.size() > 0) {
        foreach(Bar* bar, bars) {
                bar->SetClef(clef);
                bar->update();
        }
    }
}

void Track::AddBarBack(Bar* bar) {
    bar->SetClef(clef);
    if (bars.size() > 0) {
        bars.back()->SetNextBar(bar);
        bar->SetPreviousBar(bars.back());
    }
    bars.push_back(bar);
}

void Track::AddBarAt(Bar* bar, unsigned pos) { // TODO optimise to "bars.begin() + pos"
    unsigned i;
   QVector<Bar*>::iterator it = bars.begin();

    bar->SetClef(clef);
    if (pos > 0) {
        for (i = 0; i < pos-1; i++, it++); // TODO optimise
        bars.at(i)->SetNextBar(bar);       // | existing next | <--> | new |
        bar->SetPreviousBar(bars.at(i));
        i++;
        it++;
    } else {
        i = 0;
    }

    if ((int)pos <= bars.size()) {
        bars.at(i)->SetPreviousBar(bar);   // | new | <--> | existing+1 prev |
        bar->SetNextBar(bars.at(i));
    }

    bars.insert(it, bar); 
    bar->SetId(pos+1); // every next bar ID will be adjusted automatically
}

void Track::RemoveBarAt(unsigned pos) {
    unsigned id;
    assert(pos >= 0 && (int)pos < bars.size());
    
    id =  bars.at(pos)->GetId();
    bars.at(pos)->ClearNeighbour();
    bars.at(pos)->ClearNotes();
    bars.erase(bars.begin() + pos);
    if ((int)pos < bars.size()) {bars.at(pos)->SetId(id);}
    if (id == 1 && bars.size()) bars.at(0)->SetRepeatStart(true);
}

void Track::ClearBars() { 
    foreach (Bar *bar, bars) { 
        bar->ClearNotes(); 
        delete bar; 
    } 
    bars.clear(); 
}

void Track::SwapBars(Bar* bar1, Bar* bar2) { // TODO make DEQ for bars??
    Bar *bar1l, *bar1r, *bar2l, *bar2r; // left and right neighbours
    unsigned id1, id2;
    
    if (!bar1 || !bar2) {return;}
    
    id1 = bar1->GetId();
    id2 = bar2->GetId();
    bar1l = bar1->GetPrevBar();
    bar1r = bar1->GetNextBar();
    bar2l = bar2->GetPrevBar();
    bar2r = bar2->GetNextBar();
    
    // Pointer stitching
    if (bar1r == bar2) { // || bar1 == bar2l
        bar1->SetNextBar(bar2r);
        if (bar2r) {bar2r->SetPreviousBar(bar1);}
        bar2->StichPointers(bar1l, bar1);
    } else if (bar2 == bar1l) { // || bar2r == bar1
        bar1->SetPreviousBar(bar2l);
        if (bar2l) {bar2l->SetNextBar(bar1);}
        bar2->StichPointers(bar1, bar1r);
    } else {
        bar1->StichPointers(bar2l, bar2r);
        bar2->StichPointers(bar1l, bar1r);
    }
    
    // Id (recursive); must be set on most left bar and will be updated recursively
    if (id1 < id2) {
        bar2->SetId(id1);
    } else {
        bar1->SetId(id2);
    }
    
    // Vector maintenance
    //bars.erase(bars.begin() + id1-1);
    //bars.insert(bars.begin() + id1-1, bar2);
    //bars.erase(bars.begin() + id2-1);
    //bars.insert(bars.begin() + id2-1, bar1);
    bars.replace(id1-1, bar2);
    bars.replace(id2-1, bar1);
    
    // Repeat start on 1-st bar
    if ((id1 == 1 || id2 == 1) && !(bar1->IsRepeatStart() && bar2->IsRepeatStart())) { // if other bar has not rs flag - swap them
        if (bar1->GetId() == 1) {
            bar1->SetRepeatStart(true);
            bar2->SetRepeatStart(false);
        } else {
            bar1->SetRepeatStart(false);
            bar2->SetRepeatStart(true);
        }
    }
}

std::vector<QGraphicsItem*> Track::GetVisualParts() {
    std::vector<QGraphicsItem*> ret;

    foreach(Bar* bar, bars) {
        std::vector<QGraphicsItem*> visuals = bar->GetVisualParts();
        ret.push_back(bar);
        ret.insert(ret.end(), visuals.begin(), visuals.end());
    }
    
    return ret;
}

QRectF Track::boundingRect() const { 
    //qreal total_w = clef_w;
    /*foreach(Bar *current, bars) {
        total_w += current->boundingRect().width();
    }*/
    return QRectF(0, 0, clef_w, 
        spacing*4 + 2*(spacing*4) + 5); // as for 5 visual + 2*5 additional lines + extra space (just for fun)
}

qreal Track::GetVisualLength() {
    qreal len = clef_w;
    
    foreach (Bar* bar, bars) {
        len += bar->count_bar_length();
    }
    
    return len;
}

void Track::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QPointF draw_pos;                   // Current drawing position. Used by bars.
    qreal line1Y = bpos.y();
    qreal line2Y = line1Y + spacing;
    qreal line3Y = line2Y + spacing;
    qreal line4Y = line3Y + spacing;
    qreal line5Y = line4Y + spacing;
    
    QFont f;
    //quint32 treble_clef[] = {0x1d11e, 0};
    //quint32 bass_clef[] = {0x1d122, 0};
    //QString str = QString::fromUcs4( (clef == treble ? treble_clef : bass_clef) ); // Not showing :(( TODO draw it manually
    QImage treble_clef;
    QImage bass_clef;
    
    painter->setBrush(QColor(NORMAL_COLOR));
    painter->setPen(QPen(QColor(NORMAL_COLOR), 2));
    
    // Lines
    painter->drawLine(bpos.x(), line1Y, bpos.x() + clef_w, line1Y);
    painter->drawLine(bpos.x(), line2Y, bpos.x() + clef_w, line2Y);
    painter->drawLine(bpos.x(), line3Y, bpos.x() + clef_w, line3Y);
    painter->drawLine(bpos.x(), line4Y, bpos.x() + clef_w, line4Y);
    painter->drawLine(bpos.x(), line5Y, bpos.x() + clef_w, line5Y);
    
    // Borders
    //painter->setPen(QPen(Qt::black, 4)); // TODO set more apreacible look
    painter->drawRect(bpos.x(), line1Y, 2, line5Y - line1Y);
    if (bars.size() == 0) { // bar end
        painter->drawRect(bpos.x() + clef_w - 5, line1Y, 2, line5Y - line1Y);
        painter->drawRect(bpos.x() + clef_w, line1Y, 2, line5Y - line1Y);
    }
    
    // Clef
    // Unicode Musica doesn't show. Using images instead
    treble_clef.load(":/images/treble-clef.png");
    bass_clef.load(":/images/bass-clef.png");
    if (clef == treble) {
        painter->drawImage(QRectF(bpos.x() + 15, line1Y - 2*spacing, spacing*3, spacing*7.5), treble_clef); // TODO make w and h as a result of f(real_image_size)
    } else {
        painter->drawImage(QRectF(bpos.x() + 10, line1Y, spacing*4, spacing*4), bass_clef);
    }

    // Beat
    f = QFont("Stencil");
    f.setPixelSize(spacing*2+3);
    painter->setFont(f);
    painter->setPen(QPen(DATA_COLOR, 2));
    painter->drawText(bpos.x() + 55, line3Y - 3, QString::number(beat_count));
    painter->drawText(bpos.x() + 55, line5Y - 3, QString::number(beat_length));
    
    // Bars
    draw_pos = QPointF(bpos.x() + clef_w, line1Y);
    foreach(Bar* bar, bars) {
        bar->setPos(mapToScene(draw_pos));
        draw_pos.setX(draw_pos.x() + bar->count_bar_length());
    }
    
    // TAB
    // Hardcoded, yes. No time to make it pretty :(
    painter->setBrush(QColor(NORMAL_COLOR));
    painter->setPen(QPen(QColor(NORMAL_COLOR), 2));
    painter->drawText(bpos.x() + 75, line5Y + VISUAL_NOTE_VSPACING*9 + TAB_V_SPACING, "T");
    painter->drawText(bpos.x() + 75, line5Y + VISUAL_NOTE_VSPACING*11 + TAB_V_SPACING, "A");
    painter->drawText(bpos.x() + 75, line5Y + VISUAL_NOTE_VSPACING*13 + TAB_V_SPACING, "B");
}