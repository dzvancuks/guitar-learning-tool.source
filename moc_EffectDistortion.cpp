/****************************************************************************
** Meta object code from reading C++ file 'EffectDistortion.h'
**
** Created: Sat 5. Jan 20:08:44 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "EffectDistortion.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EffectDistortion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EffectDistortion[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   18,   17,   17, 0x0a,
      33,   31,   17,   17, 0x0a,
      47,   31,   17,   17, 0x0a,
      73,   67,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EffectDistortion[] = {
    "EffectDistortion\0\0l\0Level(int)\0c\0"
    "Cutoff(float)\0CutoffBySlider(int)\0"
    "input\0Process(QVector<float>*)\0"
};

void EffectDistortion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EffectDistortion *_t = static_cast<EffectDistortion *>(_o);
        switch (_id) {
        case 0: _t->Level((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->Cutoff((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->CutoffBySlider((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->Process((*reinterpret_cast< QVector<float>*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EffectDistortion::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EffectDistortion::staticMetaObject = {
    { &Effect::staticMetaObject, qt_meta_stringdata_EffectDistortion,
      qt_meta_data_EffectDistortion, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EffectDistortion::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EffectDistortion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EffectDistortion::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EffectDistortion))
        return static_cast<void*>(const_cast< EffectDistortion*>(this));
    return Effect::qt_metacast(_clname);
}

int EffectDistortion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Effect::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
