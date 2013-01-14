/****************************************************************************
** Meta object code from reading C++ file 'Metronome.h'
**
** Created: Sat 5. Jan 20:09:04 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Metronome.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Metronome.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Metronome[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x0a,
      18,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Metronome[] = {
    "Metronome\0\0Sync()\0OutputSound()\0"
};

void Metronome::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Metronome *_t = static_cast<Metronome *>(_o);
        switch (_id) {
        case 0: _t->Sync(); break;
        case 1: _t->OutputSound(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData Metronome::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Metronome::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Metronome,
      qt_meta_data_Metronome, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Metronome::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Metronome::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Metronome::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Metronome))
        return static_cast<void*>(const_cast< Metronome*>(this));
    return QObject::qt_metacast(_clname);
}

int Metronome::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
