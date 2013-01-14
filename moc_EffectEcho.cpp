/****************************************************************************
** Meta object code from reading C++ file 'EffectEcho.h'
**
** Created: Sat 5. Jan 20:08:50 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "EffectEcho.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EffectEcho.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EffectEcho[] = {

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
      18,   12,   11,   11, 0x0a,
      45,   43,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EffectEcho[] = {
    "EffectEcho\0\0input\0Process(QVector<float>*)\0"
    "d\0Decay(int)\0"
};

void EffectEcho::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EffectEcho *_t = static_cast<EffectEcho *>(_o);
        switch (_id) {
        case 0: _t->Process((*reinterpret_cast< QVector<float>*(*)>(_a[1]))); break;
        case 1: _t->Decay((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EffectEcho::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EffectEcho::staticMetaObject = {
    { &Effect::staticMetaObject, qt_meta_stringdata_EffectEcho,
      qt_meta_data_EffectEcho, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EffectEcho::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EffectEcho::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EffectEcho::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EffectEcho))
        return static_cast<void*>(const_cast< EffectEcho*>(this));
    return Effect::qt_metacast(_clname);
}

int EffectEcho::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Effect::qt_metacall(_c, _id, _a);
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
