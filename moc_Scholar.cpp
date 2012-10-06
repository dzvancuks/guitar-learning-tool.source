/****************************************************************************
** Meta object code from reading C++ file 'Scholar.h'
**
** Created: Sat 6. Oct 14:29:45 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Scholar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Scholar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Scholar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      21,    8,    8,    8, 0x0a,
      41,    8,    8,    8, 0x0a,
      59,    8,    8,    8, 0x0a,
      70,    8,    8,    8, 0x0a,
      86,   83,    8,    8, 0x0a,
     110,    8,    8,    8, 0x0a,
     133,  128,    8,    8, 0x0a,
     182,  150,    8,    8, 0x0a,
     234,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Scholar[] = {
    "Scholar\0\0ShowTuner()\0ChangeBPMbySlider()\0"
    "ChangeBPMbyText()\0PlayStop()\0OpenLesson()\0"
    "nw\0ResizeSceneWidth(qreal)\0PostPreparation()\0"
    "note\0FetchNote(Note*)\0"
    "result,freq,pitch,note,logPower\0"
    "SinglePitchData(bool,double,int,const char*,double)\0"
    "CarriageFinished()\0"
};

void Scholar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Scholar *_t = static_cast<Scholar *>(_o);
        switch (_id) {
        case 0: _t->ShowTuner(); break;
        case 1: _t->ChangeBPMbySlider(); break;
        case 2: _t->ChangeBPMbyText(); break;
        case 3: _t->PlayStop(); break;
        case 4: _t->OpenLesson(); break;
        case 5: _t->ResizeSceneWidth((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 6: _t->PostPreparation(); break;
        case 7: _t->FetchNote((*reinterpret_cast< Note*(*)>(_a[1]))); break;
        case 8: _t->SinglePitchData((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const char*(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 9: _t->CarriageFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Scholar::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Scholar::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Scholar,
      qt_meta_data_Scholar, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Scholar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Scholar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Scholar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Scholar))
        return static_cast<void*>(const_cast< Scholar*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Scholar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
