/****************************************************************************
** Meta object code from reading C++ file 'Carriage.h'
**
** Created: Sat 5. Jan 20:08:55 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Carriage.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Carriage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Carriage[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      21,    9,    9,    9, 0x05,
      37,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Carriage[] = {
    "Carriage\0\0Finished()\0PassNote(Note*)\0"
    "NewBar()\0ClearTimer()\0"
};

void Carriage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Carriage *_t = static_cast<Carriage *>(_o);
        switch (_id) {
        case 0: _t->Finished(); break;
        case 1: _t->PassNote((*reinterpret_cast< Note*(*)>(_a[1]))); break;
        case 2: _t->NewBar(); break;
        case 3: _t->ClearTimer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Carriage::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Carriage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Carriage,
      qt_meta_data_Carriage, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Carriage::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Carriage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Carriage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Carriage))
        return static_cast<void*>(const_cast< Carriage*>(this));
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Carriage*>(this));
    if (!strcmp(_clname, "com.trolltech.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(const_cast< Carriage*>(this));
    return QObject::qt_metacast(_clname);
}

int Carriage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void Carriage::Finished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void Carriage::PassNote(Note * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Carriage::NewBar()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}
QT_END_MOC_NAMESPACE
