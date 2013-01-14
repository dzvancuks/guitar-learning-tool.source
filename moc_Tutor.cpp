/****************************************************************************
** Meta object code from reading C++ file 'Tutor.h'
**
** Created: Sat 5. Jan 20:08:30 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Tutor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Tutor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Tutor[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      52,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,    6,    6,    6, 0x0a,
      36,    6,    6,    6, 0x0a,
      43,    6,    6,    6, 0x0a,
      50,    6,    6,    6, 0x0a,
      59,    6,    6,    6, 0x0a,
      74,   71,    6,    6, 0x0a,
      98,    6,    6,    6, 0x0a,
     112,    6,    6,    6, 0x0a,
     128,    6,    6,    6, 0x0a,
     143,    6,    6,    6, 0x0a,
     158,    6,    6,    6, 0x0a,
     175,    6,    6,    6, 0x0a,
     184,    6,    6,    6, 0x0a,
     193,    6,    6,    6, 0x0a,
     209,    6,    6,    6, 0x0a,
     224,    6,    6,    6, 0x0a,
     241,    6,    6,    6, 0x0a,
     256,    6,    6,    6, 0x0a,
     274,    6,    6,    6, 0x0a,
     285,    6,    6,    6, 0x0a,
     295,    6,    6,    6, 0x0a,
     305,    6,    6,    6, 0x0a,
     322,    6,    6,    6, 0x0a,
     338,    6,    6,    6, 0x0a,
     354,    6,    6,    6, 0x0a,
     373,    6,    6,    6, 0x0a,
     391,    6,    6,    6, 0x0a,
     406,    6,    6,    6, 0x0a,
     423,    6,    6,    6, 0x0a,
     441,    6,    6,    6, 0x0a,
     461,    6,    6,    6, 0x0a,
     475,    6,    6,    6, 0x0a,
     485,    6,    6,    6, 0x0a,
     503,    6,    6,    6, 0x0a,
     513,    6,    6,    6, 0x0a,
     522,    6,    6,    6, 0x0a,
     533,    6,    6,    6, 0x0a,
     549,    6,    6,    6, 0x0a,
     563,    6,    6,    6, 0x0a,
     581,    6,    6,    6, 0x0a,
     607,  601,    6,    6, 0x0a,
     634,  601,    6,    6, 0x0a,
     673,  601,    6,    6, 0x0a,
     701,  601,    6,    6, 0x0a,
     741,  601,    6,    6, 0x0a,
     769,    6,    6,    6, 0x0a,
     781,    6,    6,    6, 0x0a,
     791,    6,    6,    6, 0x0a,
     802,    6,    6,    6, 0x0a,
     817,    6,    6,    6, 0x0a,
     845,  843,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Tutor[] = {
    "Tutor\0\0PassToScholar(Lesson*)\0New()\0"
    "Open()\0Save()\0SaveAs()\0ShowAbout()\0"
    "nw\0ResizeSceneWidth(qreal)\0SceneUpdate()\0"
    "BPMChanged(int)\0BCChanged(int)\0"
    "BLChanged(int)\0ClefChanged(int)\0"
    "AddBar()\0DelBar()\0ShiftRightBar()\0"
    "ShiftLeftBar()\0RepeatStart(int)\0"
    "RepeatEnd(int)\0RepeatOnNext(int)\0"
    "BarChord()\0AddNote()\0DelNote()\0"
    "ShiftRightNote()\0ShiftLeftNote()\0"
    "NoteLength(int)\0NoteExtension(int)\0"
    "NoteContinue(int)\0NoteSlide(int)\0"
    "NoteVibrato(int)\0NoteGrouping(int)\0"
    "NoteUngrouping(int)\0NoteHOPO(int)\0"
    "AddTone()\0AddToneSN_Chord()\0DelTone()\0"
    "ToneUp()\0ToneDown()\0ToneString(int)\0"
    "ToneRest(int)\0BarSelected(Bar*)\0"
    "NoteSelected(Note*)\0state\0"
    "ChangeBarWidgetFrame(bool)\0"
    "ChangeBarWidgetFrameAllButAddBtn(bool)\0"
    "ChangeNoteWidgetFrame(bool)\0"
    "ChangeNoteWidgetFrameAllButAddBtn(bool)\0"
    "ChangeToneWidgetFrame(bool)\0TrackPlay()\0"
    "BarPlay()\0NotePlay()\0StartScholar()\0"
    "FetchFromScholar(Lesson*)\0,\0"
    "SubstituteNote(Note*,Note*)\0"
};

void Tutor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Tutor *_t = static_cast<Tutor *>(_o);
        switch (_id) {
        case 0: _t->PassToScholar((*reinterpret_cast< Lesson*(*)>(_a[1]))); break;
        case 1: _t->New(); break;
        case 2: _t->Open(); break;
        case 3: _t->Save(); break;
        case 4: _t->SaveAs(); break;
        case 5: _t->ShowAbout(); break;
        case 6: _t->ResizeSceneWidth((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 7: _t->SceneUpdate(); break;
        case 8: _t->BPMChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->BCChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->BLChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->ClefChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->AddBar(); break;
        case 13: _t->DelBar(); break;
        case 14: _t->ShiftRightBar(); break;
        case 15: _t->ShiftLeftBar(); break;
        case 16: _t->RepeatStart((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->RepeatEnd((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->RepeatOnNext((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->BarChord(); break;
        case 20: _t->AddNote(); break;
        case 21: _t->DelNote(); break;
        case 22: _t->ShiftRightNote(); break;
        case 23: _t->ShiftLeftNote(); break;
        case 24: _t->NoteLength((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->NoteExtension((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->NoteContinue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->NoteSlide((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->NoteVibrato((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->NoteGrouping((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->NoteUngrouping((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 31: _t->NoteHOPO((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 32: _t->AddTone(); break;
        case 33: _t->AddToneSN_Chord(); break;
        case 34: _t->DelTone(); break;
        case 35: _t->ToneUp(); break;
        case 36: _t->ToneDown(); break;
        case 37: _t->ToneString((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->ToneRest((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->BarSelected((*reinterpret_cast< Bar*(*)>(_a[1]))); break;
        case 40: _t->NoteSelected((*reinterpret_cast< Note*(*)>(_a[1]))); break;
        case 41: _t->ChangeBarWidgetFrame((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 42: _t->ChangeBarWidgetFrameAllButAddBtn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 43: _t->ChangeNoteWidgetFrame((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 44: _t->ChangeNoteWidgetFrameAllButAddBtn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 45: _t->ChangeToneWidgetFrame((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 46: _t->TrackPlay(); break;
        case 47: _t->BarPlay(); break;
        case 48: _t->NotePlay(); break;
        case 49: _t->StartScholar(); break;
        case 50: _t->FetchFromScholar((*reinterpret_cast< Lesson*(*)>(_a[1]))); break;
        case 51: _t->SubstituteNote((*reinterpret_cast< Note*(*)>(_a[1])),(*reinterpret_cast< Note*(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Tutor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Tutor::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Tutor,
      qt_meta_data_Tutor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Tutor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Tutor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Tutor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Tutor))
        return static_cast<void*>(const_cast< Tutor*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Tutor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 52)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 52;
    }
    return _id;
}

// SIGNAL 0
void Tutor::PassToScholar(Lesson * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
