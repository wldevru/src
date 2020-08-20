/****************************************************************************
** Meta object code from reading C++ file 'wldevice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlmotion/wldevice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wldevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLDevice_t {
    QByteArrayData data[29];
    char stringdata0[374];
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
QT_MOC_LITERAL(3, 25, 14), // "createdModules"
QT_MOC_LITERAL(4, 40, 11), // "reconnected"
QT_MOC_LITERAL(5, 52, 14), // "changedConnect"
QT_MOC_LITERAL(6, 67, 14), // "changedModules"
QT_MOC_LITERAL(7, 82, 12), // "changedReady"
QT_MOC_LITERAL(8, 95, 11), // "changedProp"
QT_MOC_LITERAL(9, 107, 13), // "changedStatus"
QT_MOC_LITERAL(10, 121, 12), // "statusDevice"
QT_MOC_LITERAL(11, 134, 12), // "changedUID96"
QT_MOC_LITERAL(12, 147, 14), // "changedVersion"
QT_MOC_LITERAL(13, 162, 13), // "updateModules"
QT_MOC_LITERAL(14, 176, 11), // "sendEthData"
QT_MOC_LITERAL(15, 188, 8), // "readSlot"
QT_MOC_LITERAL(16, 197, 17), // "onErrorSerialPort"
QT_MOC_LITERAL(17, 215, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(18, 244, 15), // "serialPortError"
QT_MOC_LITERAL(19, 260, 8), // "sendData"
QT_MOC_LITERAL(20, 269, 9), // "startSend"
QT_MOC_LITERAL(21, 279, 4), // "data"
QT_MOC_LITERAL(22, 284, 13), // "removeModules"
QT_MOC_LITERAL(23, 298, 11), // "callModules"
QT_MOC_LITERAL(24, 310, 11), // "callVersion"
QT_MOC_LITERAL(25, 322, 19), // "reconnectSerialPort"
QT_MOC_LITERAL(26, 342, 12), // "closeConnect"
QT_MOC_LITERAL(27, 355, 10), // "callStatus"
QT_MOC_LITERAL(28, 366, 7) // "callUID"

    },
    "WLDevice\0readDataDevice\0\0createdModules\0"
    "reconnected\0changedConnect\0changedModules\0"
    "changedReady\0changedProp\0changedStatus\0"
    "statusDevice\0changedUID96\0changedVersion\0"
    "updateModules\0sendEthData\0readSlot\0"
    "onErrorSerialPort\0QSerialPort::SerialPortError\0"
    "serialPortError\0sendData\0startSend\0"
    "data\0removeModules\0callModules\0"
    "callVersion\0reconnectSerialPort\0"
    "closeConnect\0callStatus\0callUID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLDevice[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  129,    2, 0x06 /* Public */,
       3,    0,  130,    2, 0x06 /* Public */,
       4,    0,  131,    2, 0x06 /* Public */,
       5,    1,  132,    2, 0x06 /* Public */,
       6,    1,  135,    2, 0x06 /* Public */,
       7,    1,  138,    2, 0x06 /* Public */,
       8,    1,  141,    2, 0x06 /* Public */,
       9,    1,  144,    2, 0x06 /* Public */,
      11,    1,  147,    2, 0x06 /* Public */,
      12,    1,  150,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,  153,    2, 0x08 /* Private */,
      14,    0,  154,    2, 0x08 /* Private */,
      15,    0,  155,    2, 0x08 /* Private */,
      16,    1,  156,    2, 0x08 /* Private */,
      19,    0,  159,    2, 0x08 /* Private */,
      20,    1,  160,    2, 0x08 /* Private */,
      22,    0,  163,    2, 0x0a /* Public */,
      23,    0,  164,    2, 0x0a /* Public */,
      24,    0,  165,    2, 0x0a /* Public */,
      25,    0,  166,    2, 0x0a /* Public */,
      26,    0,  167,    2, 0x0a /* Public */,
      27,    0,  168,    2, 0x0a /* Public */,
      28,    0,  169,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::UInt,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   21,
    QMetaType::Void,
    QMetaType::Void,
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
        case 1: _t->createdModules(); break;
        case 2: _t->reconnected(); break;
        case 3: _t->changedConnect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->changedModules((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->changedReady((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->changedProp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->changedStatus((*reinterpret_cast< statusDevice(*)>(_a[1]))); break;
        case 8: _t->changedUID96((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->changedVersion((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 10: _t->updateModules(); break;
        case 11: _t->sendEthData(); break;
        case 12: _t->readSlot(); break;
        case 13: _t->onErrorSerialPort((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 14: _t->sendData(); break;
        case 15: _t->startSend((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 16: _t->removeModules(); break;
        case 17: _t->callModules(); break;
        case 18: _t->callVersion(); break;
        case 19: _t->reconnectSerialPort(); break;
        case 20: _t->closeConnect(); break;
        case 21: _t->callStatus(); break;
        case 22: _t->callUID(); break;
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
            using _t = void (WLDevice::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::createdModules)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::reconnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::changedConnect)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::changedModules)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::changedReady)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::changedProp)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(statusDevice );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::changedStatus)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::changedUID96)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (WLDevice::*)(quint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDevice::changedVersion)) {
                *result = 9;
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
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void WLDevice::readDataDevice()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WLDevice::createdModules()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WLDevice::reconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WLDevice::changedConnect(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WLDevice::changedModules(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WLDevice::changedReady(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void WLDevice::changedProp(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void WLDevice::changedStatus(statusDevice _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void WLDevice::changedUID96(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void WLDevice::changedVersion(quint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
