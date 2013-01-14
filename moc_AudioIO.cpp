/****************************************************************************
** Meta object code from reading C++ file 'AudioIO.h'
**
** Created: Sat 5. Jan 20:08:36 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "AudioIO.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AudioIO.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AudioIO[] = {

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
       9,    8,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      22,    8,    8,    8, 0x0a,
      32,    8,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AudioIO[] = {
    "AudioIO\0\0InputReady()\0Destroy()\0"
    "Timeout()\0"
};

void AudioIO::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AudioIO *_t = static_cast<AudioIO *>(_o);
        switch (_id) {
        case 0: _t->InputReady(); break;
        case 1: _t->Destroy(); break;
        case 2: _t->Timeout(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AudioIO::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AudioIO::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AudioIO,
      qt_meta_data_AudioIO, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AudioIO::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AudioIO::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AudioIO::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AudioIO))
        return static_cast<void*>(const_cast< AudioIO*>(this));
    return QObject::qt_metacast(_clname);
}

int AudioIO::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void AudioIO::InputReady()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
