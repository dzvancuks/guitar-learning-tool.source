/****************************************************************************
** Meta object code from reading C++ file 'SingleToneAnalyzer.h'
**
** Created: Sat 6. Oct 13:27:03 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SingleToneAnalyzer.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SingleToneAnalyzer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_SingleToneAnalyzer[] = {

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
      52,   20,   19,   19, 0x05,

 // slots: signature, parameters, type, tag, flags
     105,   19,   19,   19, 0x0a,
     120,   19,   19,   19, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SingleToneAnalyzer[] = {
    "SingleToneAnalyzer\0\0result,freq,pitch,note,logPower\0"
    "sendAnalyzerData(bool,double,int,const char*,double)\0"
    "startProcess()\0stopProcess()\0"
};

void SingleToneAnalyzer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        SingleToneAnalyzer *_t = static_cast<SingleToneAnalyzer *>(_o);
        switch (_id) {
        case 0: _t->sendAnalyzerData((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const char*(*)>(_a[4])),(*reinterpret_cast< double(*)>(_a[5]))); break;
        case 1: _t->startProcess(); break;
        case 2: _t->stopProcess(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData SingleToneAnalyzer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject SingleToneAnalyzer::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SingleToneAnalyzer,
      qt_meta_data_SingleToneAnalyzer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &SingleToneAnalyzer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *SingleToneAnalyzer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *SingleToneAnalyzer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SingleToneAnalyzer))
        return static_cast<void*>(const_cast< SingleToneAnalyzer*>(this));
    return QThread::qt_metacast(_clname);
}

int SingleToneAnalyzer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void SingleToneAnalyzer::sendAnalyzerData(bool _t1, double _t2, int _t3, const char * _t4, double _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
