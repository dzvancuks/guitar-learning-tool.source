/****************************************************************************
** Meta object code from reading C++ file 'EffectPump.h'
**
** Created: Sat 5. Jan 20:08:47 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "EffectPump.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EffectPump.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EffectPump[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      27,   25,   11,   11, 0x0a,
      44,   25,   11,   11, 0x0a,
      61,   25,   11,   11, 0x0a,
      78,   11,   11,   11, 0x0a,
      94,   11,   11,   11, 0x0a,
     110,   11,   11,   11, 0x0a,
     126,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EffectPump[] = {
    "EffectPump\0\0FetchSound()\0i\0LoadEffect1(int)\0"
    "LoadEffect2(int)\0LoadEffect3(int)\0"
    "UnloadEffect1()\0UnloadEffect2()\0"
    "UnloadEffect3()\0UnloadAllEffects()\0"
};

void EffectPump::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EffectPump *_t = static_cast<EffectPump *>(_o);
        switch (_id) {
        case 0: _t->FetchSound(); break;
        case 1: _t->LoadEffect1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->LoadEffect2((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->LoadEffect3((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->UnloadEffect1(); break;
        case 5: _t->UnloadEffect2(); break;
        case 6: _t->UnloadEffect3(); break;
        case 7: _t->UnloadAllEffects(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EffectPump::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EffectPump::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_EffectPump,
      qt_meta_data_EffectPump, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EffectPump::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EffectPump::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EffectPump::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EffectPump))
        return static_cast<void*>(const_cast< EffectPump*>(this));
    return QWidget::qt_metacast(_clname);
}

int EffectPump::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
