/* 
 * File:   Note.h
 * Author: astral
 *
 * Created on 21 Август 2012 г., 22:35
 */

#ifndef NOTE_H
#define	NOTE_H

#include <QtGui/QtGui>
#include <cassert>

#define NOTES_PER_OCTAVE 12
#define OCTAVES 9
#define TOTAL_TONES 108
static const double octave_notes[TOTAL_TONES] = {
    /* C       C#/Db       D       D#/Eb       E         F       F#/Gb       G       G#/Ab       A       A#/Bb       B */
    16.352,   17.324,   18.354,   19.445,   20.602,   21.827,   23.125,   24.500,   25.957,   27.500,   29.135,   30.868,   // Sub Contra
    32.703,   34.648,   36.708,   38.891,   41.203,   43.654,   46.249,   48.999,   51.913,   55.000,   58.270,   61.735,   // Contra
    65.406,   69.296,   73.416,   77.782,   82.407,   87.307,   92.499,   97.999,   103.826,  110.000,  116.541,  123.471,  // Great
    130.813,  138.591,  146.832,  155.563,  164.814,  174.614,  184.997,  195.998,  207.652,  220.000,  233.082,  246.942,  // Small
    261.626,  277.183,  293.665,  311.127,  329.628,  349.228,  369.994,  391.995,  415.305,  440.000,  466.164,  493.883,  // 1
    523.251,  554.365,  587.330,  622.254,  659.255,  698.456,  739.989,  783.991,  830.609,  880.000,  932.328,  987.767,  // 2
    1046.502, 1108.731, 1174.659, 1244.508, 1318.510, 1396.913, 1479.978, 1567.982, 1661.219, 1760.000, 1864.655, 1975.533, // 3
    2093.005, 2217.461, 2349.318, 2489.016, 2637.020, 2793.826, 2959.955, 3135.963, 3322.438, 3520.000, 3729.310, 3951.066, // 4
    4186.009, 4434.922, 4698.636, 4978.032, 5274.041, 5587.652, 5919.911, 6271.927, 6644.875, 7040.000, 7458.620, 7902.133  // 5
};

typedef enum NoteLengthE {
    nl64 = 1, // as for 1/64
    nl32 = 2,
    nl16 = 4,
    nl8 = 8,
    nl4 = 16,
    nl2 = 32,
    nl1 = 64  // as for 1/1 is 64 times of 64-th
} NoteLength;

/* Structure that used to adjust bar VISUAL size and carriage speed according to note size
 * Notes from one- 64-th to 8-th should be same size, but different carriage speed;
 * 4-th to whole (1) note should differ by 2x space, but same carriage speed.
 * Dots (half sizes) should extend size by 0.5, but remain speed. I.e. 32.. = sz(1) + sz(0.5) + sz(0.25)
 * All values are coefficient, not real values.
 */
typedef struct VisualSizeSpeedS {
    qreal size;
    qreal speed;
} VisualSizeSpeed;

extern VisualSizeSpeed GlobalGetVisualSizeSpeed(NoteLength length, unsigned extension);

#define VISUAL_SIZE 10 // px per size coefficient
#define VISUAL_NOTE_SPACING (VISUAL_SIZE * 2)
#define VISUAL_NOTE_VSPACING (VISUAL_SIZE)
#define VISUAL_HALFNOTE_VSPACING (VISUAL_NOTE_VSPACING / 2)
#define AVG_NOTE_TAIL (VISUAL_SIZE * 3)
#define VISUAL_SINGLE_TAIL_VSPACING 4
#define NOTE_COLOR Qt::black

class Note : public QObject, public QGraphicsItem {
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    Note(NoteLength nlength = nl1, unsigned nextension = 0);
    Note(const Note& orig);
    virtual ~Note();
    
    //void SetParentBar (void *bar) {this->bar = bar;}
    //void* GetParentBar () {return this->bar;}
    
    // TODO return true if continueTo != NULL and rewrite flags to pointers
    void SetContinuation(Note *n) { continuation = n; } 
    void SetContinued   (Note *n) { continued    = n; } // must be call in pair for both affected notes
    void RemoveContinuation() { continuation = NULL; }
    void RemoveContinued   () { continued    = NULL; } // must be call in pair for both affected notes
    bool IsContinuation() { return continuation != NULL; }
    bool IsContinued() { return continued != NULL; }
    // Get ...
    
    void SetSlide (Note *n) { slide  = n; }
    void SetSlided(Note *n) { slided = n; } // must be call in pair for both affected notes
    void RemoveSlide () { slide  = NULL; }
    void RemoveSlided() { slided = NULL; } // must be call in pair for both affected notes
    bool IsSlide() { return slide != NULL; }
    bool IsSlided() { return slided != NULL; }
    // Get ...
    
    void SetVibrato() { vibrato = true; }
    void RemoveVibrato() { vibrato = false; }
    bool IsVibrato() { return vibrato; }
    
    void SetHO() { HO = true; }
    void SetPO() { PO = true; }
    void RemoveHO() { HO = false; }
    void RemovePO() { PO = false; }
    bool IsHO() { return HO; }
    bool IsPO() { return PO; }
    
    void SetGrouping  (unsigned n) { grouping   = n; } // from current note and forward
    void SetUngrouping(unsigned n) { ungrouping = n; }
    unsigned GetGrouping() { return grouping; }
    unsigned GetUngrouping() { return ungrouping; }
    void SetInGroup (bool val) { in_group = val; }
    bool GetInGroup ()         { return in_group; }
    
    void SetLength(NoteLength l) { length = l; }
    NoteLength GetBasicLength() { return length; } // Rename on *Length
    void SetExtension(unsigned e) { assert(e < 3); extension = e; }
    unsigned GetExtensionCount() { return extension; }
    unsigned GetLength() {  // Rename on *VisualLength
        unsigned len = length;
        for (unsigned i = 0; i < extension; i++) { len += (length/(unsigned)pow(2.0, (double)(i+1)) );} // TODO test: doesn't work on nl4 + 1
        return len; 
    }
    
    VisualSizeSpeed GetVisualSizeSpeed() {
        return GlobalGetVisualSizeSpeed(this->length, this->extension);
    }
    
    // Static member to find position in octave_notes by tone frequency; returns pos < TOTAL_TONES or -1
    static int FreqToOctavePos (double freq);
    
    // Graphics sfuff
    QRectF boundingRect() const { 
        return QRectF(-VISUAL_SIZE*0.5, -VISUAL_SIZE*0.5 + 1, VISUAL_SIZE, VISUAL_SIZE*0.75);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {}
    
    // Mouse pointing routine
    void SetActive(bool state) { active = state; }
    
protected:
    NoteLength length;
    unsigned   extension; // dot extension by half length.

    //void      *bar; // parent
    
    // TODO dispose bool flags and leave pointers only?
    Note      *continuation; // o|  |  o| - note connection between bars
    Note      *continued;    //  \__|__/
    //Note      *continueTo;
    //Note      *continuedFrom;// pointers for 'continue' drawings
    
    Note      *slide;        //   | /o|   - slide connection between notes // TODO add slide to/slided from note reference
    Note      *slided;       //  o|/        // currently, reference is on next/previous note
    //Note      *slideTo;
    //Note      *slidedFrom;   // pointers for 'slide' drawings
  
    bool       vibrato;      // currently, only for visual representation // TODO add analysis for vibrato input
    
    bool       HO;           // Hammer on visuals 
    bool       PO;           // Pull off visuals  - Both are only for visuals; analysed same as normal note // TODO make lower noize floor for HO/PO
    
    unsigned   grouping;     // triplets and so on: 3, 5, 6, 7, 9 and 10
    unsigned   ungrouping;   // duplet and quadruplet: 2 and 4
    bool       in_group;     // true if this note is included in other group
    
    bool active; // selected alternative
};

#endif	/* NOTE_H */

