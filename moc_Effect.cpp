/****************************************************************************
** Meta object code from reading C++ file 'Effect.h'
**
** Created: Sat 5. Jan 20:08:52 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Effect.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Effect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Effect[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      22,   16,    7,    7, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Effect[] = {
    "Effect\0\0Ready()\0input\0Process(QVector<float>*)\0"
};

void Effect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Effect *_t = static_cast<Effect *>(_o);
        switch (_id) {
        case 0: _t->Ready(); break;
        case 1: _t->Process((*reinterpret_cast< QVector<float>*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Effect::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Effect::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Effect,
      qt_meta_data_Effect, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Effect::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Effect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Effect::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Effect))
        return static_cast<void*>(const_cast< Effect*>(this));
    return QWidget::qt_metacast(_clname);
}

int Effect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void Effect::Ready()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
