/****************************************************************************
** Meta object code from reading C++ file 'Scholar.h'
**
** Created: Sat 5. Jan 20:08:38 2013
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
static const uint qt_meta_data_Result[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

static const char qt_meta_stringdata_Result[] = {
    "Result\0"
};

void Result::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Result::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Result::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Result,
      qt_meta_data_Result, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Result::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Result::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Result::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Result))
        return static_cast<void*>(const_cast< Result*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Result*>(this));
    if (!strcmp(_clname, "com.trolltech.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Result*>(this));
    return QObject::qt_metacast(_clname);
}

int Result::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
static const uint qt_meta_data_Scholar[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      30,    8,    8,    8, 0x0a,
      42,    8,    8,    8, 0x0a,
      56,    8,    8,    8, 0x0a,
      68,    8,    8,    8, 0x0a,
      88,    8,    8,    8, 0x0a,
     106,    8,    8,    8, 0x0a,
     117,    8,    8,    8, 0x0a,
     130,    8,    8,    8, 0x0a,
     145,    8,    8,    8, 0x0a,
     175,  172,    8,    8, 0x0a,
     199,    8,    8,    8, 0x0a,
     222,  217,    8,    8, 0x0a,
     271,  239,    8,    8, 0x0a,
     325,  323,    8,    8, 0x0a,
     347,    8,    8,    8, 0x0a,
     366,    8,    8,    8, 0x0a,
     379,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Scholar[] = {
    "Scholar\0\0PassToTutor(Lesson*)\0ShowTuner()\0"
    "DeleteTuner()\0ShowAbout()\0ChangeBPMbySlider()\0"
    "ChangeBPMbyText()\0PlayStop()\0OpenLesson()\0"
    "ChangeVolume()\0ChangeMetronomeState(bool)\0"
    "nw\0ResizeSceneWidth(qreal)\0PostPreparation()\0"
    "note\0FetchNote(Note*)\0"
    "result,freq,pitch,note,logPower\0"
    "SinglePitchData(bool,double,int,const char*,double)\0"
    ",\0ChordData(float*,int)\0CarriageFinished()\0"
    "StartTutor()\0FetchFromTutor(Lesson*)\0"
};

void Scholar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Scholar *_t = static_cast<Scholar *>(_o);
        switch (_id) {
        case 0: _t->PassToTutor((*reinterpret_cast< Lesson*(*)>(_a[1]))); break;
        case 1: _t->ShowTuner(); break;
        case 2: _t->DeleteTuner(); break;
        case 3: _t->ShowAbout(); break;
        case 4: _t->ChangeBPMbySlider(); break;
        case 5: _t->ChangeBPMbyText(); break;
        case 6: _t->PlayStop(); break;
        case 7: _t->OpenLesson(); break;
        case 8: _t->ChangeVolume(); break;
        case 9: _t->ChangeMetronomeState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->ResizeSceneWidth((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 11: _t->PostPreparation(); break;
        case 12: _t->FetchNote((*reinterpret_cast< Note*(*)>(_a[1]))); break;
        case 13: _t->SinglePitchData((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const char*(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 14: _t->ChordData((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->CarriageFinished(); break;
        case 16: _t->StartTutor(); break;
        case 17: _t->FetchFromTutor((*reinterpret_cast< Lesson*(*)>(_a[1]))); break;
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
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void Scholar::PassToTutor(Lesson * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
