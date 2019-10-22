/****************************************************************************
** Meta object code from reading C++ file 'WLDevice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../WLMotion/WLDevice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WLDevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLDevice_t {
    QByteArrayData data[22];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLDevice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLDevice_t qt_meta_stringdata_WLDevice = {
    {
QT_MOC_LITERAL(0, 0, 8), // "WLDevice"
QT_MOC_LITERAL(1, 9, 14), // "readDataDevice"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 11), // "sendMessage"
QT_MOC_LITERAL(4, 37, 15), // "ChangedErrorCut"
QT_MOC_LITERAL(5, 53, 5), // "index"
QT_MOC_LITERAL(6, 59, 5), // "error"
QT_MOC_LITERAL(7, 65, 14), // "ChangedConnect"
QT_MOC_LITERAL(8, 80, 14), // "ChangedModules"
QT_MOC_LITERAL(9, 95, 12), // "ChangedReady"
QT_MOC_LITERAL(10, 108, 11), // "ChangedProp"
QT_MOC_LITERAL(11, 120, 12), // "ChangedUID96"
QT_MOC_LITERAL(12, 133, 8), // "quint32*"
QT_MOC_LITERAL(13, 142, 8), // "readSlot"
QT_MOC_LITERAL(14, 151, 8), // "sendData"
QT_MOC_LITERAL(15, 160, 9), // "startSend"
QT_MOC_LITERAL(16, 170, 4), // "data"
QT_MOC_LITERAL(17, 175, 13), // "removeModules"
QT_MOC_LITERAL(18, 189, 11), // "callModules"
QT_MOC_LITERAL(19, 201, 19), // "reconnectSerialPort"
QT_MOC_LITERAL(20, 221, 8), // "callProp"
QT_MOC_LITERAL(21, 230, 7) // "callUID"

    },
    "WLDevice\0readDataDevice\0\0sendMessage\0"
    "ChangedErrorCut\0index\0error\0ChangedConnect\0"
    "ChangedModules\0ChangedReady\0ChangedProp\0"
    "ChangedUID96\0quint32*\0readSlot\0sendData\0"
    "startSend\0data\0removeModules\0callModules\0"
    "reconnectSerialPort\0callProp\0callUID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLDevice[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    3,   95,    2, 0x06 /* Public */,
       4,    2,  102,    2, 0x06 /* Public */,
       7,    1,  107,    2, 0x06 /* Public */,
       8,    1,  110,    2, 0x06 /* Public */,
       9,    1,  113,    2, 0x06 /* Public */,
      10,    1,  116,    2, 0x06 /* Public */,
      11,    1,  119,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  122,    2, 0x08 /* Private */,
      14,    0,  123,    2, 0x08 /* Private */,
      15,    1,  124,    2, 0x08 /* Private */,
      17,    0,  127,    2, 0x0a /* Public */,
      18,    0,  128,    2, 0x0a /* Public */,
      19,    0,  129,    2, 0x0a /* Public */,
      20,    0,  130,    2, 0x08 /* Private */,
      21,    0,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::UChar, QMetaType::UChar,    5,    6,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 12,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WLDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLDevice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readDataDevice(); break;
        case 1: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 2: _t->ChangedErrorCut((*reinterpret_cast< quint8(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 3: _t->ChangedConnect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->ChangedModules((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->ChangedReady((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->ChangedProp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->ChangedUID96((*reinterpret_cast< quint32*(*)>(_a[1]))); break;
        case 8: _t->readSlot(); break;
        case 9: _t->sendData(); break;
        case 10: _t->startSend((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 11: _t->removeModules(); break;
        case 12: _t->callModules(); break;
        case 13: _t->reconnectSerialPort(); break;
        case 14: _t->callProp(); break;
        case 15: _t->callUID(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLDevice::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::readDataDevice)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(QString , QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::sendMessage)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(quint8 , quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::ChangedErrorCut)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::ChangedConnect)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::ChangedModules)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::ChangedReady)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::ChangedProp)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(quint32 * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::ChangedUID96)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLDevice::staticMetaObject = { {
    &WLModule::staticMetaObject,
    qt_meta_stringdata_WLDevice.data,
    qt_meta_data_WLDevice,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLDevice.stringdata0))
        return static_cast<void*>(this);
    return WLModule::qt_metacast(_clname);
}

int WLDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WLModule::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void WLDevice::readDataDevice()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WLDevice::sendMessage(QString _t1, QString _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WLDevice::ChangedErrorCut(quint8 _t1, quint8 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WLDevice::ChangedConnect(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WLDevice::ChangedModules(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WLDevice::ChangedReady(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void WLDevice::ChangedProp(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void WLDevice::ChangedUID96(quint32 * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
