/****************************************************************************
** Meta object code from reading C++ file 'ChordAnalyzer.h'
**
** Created: Sat 5. Jan 20:08:57 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ChordAnalyzer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChordAnalyzer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ChordAnalyzer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      46,   14,   14,   14, 0x0a,
      61,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_ChordAnalyzer[] = {
    "ChordAnalyzer\0\0,\0sendAnalyzerData(float*,int)\0"
    "startProcess()\0stopProcess()\0"
};

void ChordAnalyzer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ChordAnalyzer *_t = static_cast<ChordAnalyzer *>(_o);
        switch (_id) {
        case 0: _t->sendAnalyzerData((*reinterpret_cast< float*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->startProcess(); break;
        case 2: _t->stopProcess(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ChordAnalyzer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ChordAnalyzer::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ChordAnalyzer,
      qt_meta_data_ChordAnalyzer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ChordAnalyzer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ChordAnalyzer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ChordAnalyzer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ChordAnalyzer))
        return static_cast<void*>(const_cast< ChordAnalyzer*>(this));
    return QThread::qt_metacast(_clname);
}

int ChordAnalyzer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void ChordAnalyzer::sendAnalyzerData(float * _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
