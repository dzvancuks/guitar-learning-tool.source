/****************************************************************************
** Meta object code from reading C++ file 'Tuner.h'
**
** Created: Sat 5. Jan 20:08:33 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Tuner.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Tuner.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Tuner[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x05,

 // slots: signature, parameters, type, tag, flags
      53,   21,    6,    6, 0x0a,
      94,    6,    6,    6, 0x08,
     107,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Tuner[] = {
    "Tuner\0\0TunerClosed()\0"
    "result,freq,pitch,note,logPower\0"
    "Tune(bool,double,int,const char*,double)\0"
    "SetStrings()\0SetCurrString()\0"
};

void Tuner::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Tuner *_t = static_cast<Tuner *>(_o);
        switch (_id) {
        case 0: _t->TunerClosed(); break;
        case 1: _t->Tune((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const char*(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 2: _t->SetStrings(); break;
        case 3: _t->SetCurrString(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Tuner::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Tuner::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Tuner,
      qt_meta_data_Tuner, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Tuner::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Tuner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Tuner::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Tuner))
        return static_cast<void*>(const_cast< Tuner*>(this));
    return QDialog::qt_metacast(_clname);
}

int Tuner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Tuner::TunerClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
