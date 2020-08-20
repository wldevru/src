/****************************************************************************
** Meta object code from reading C++ file 'wlmoduleconnect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlmotion/modules/wlmoduleconnect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlmoduleconnect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLModuleConnect_t {
    QByteArrayData data[9];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLModuleConnect_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLModuleConnect_t qt_meta_stringdata_WLModuleConnect = {
    {
QT_MOC_LITERAL(0, 0, 15), // "WLModuleConnect"
QT_MOC_LITERAL(1, 16, 12), // "timeoutHeart"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 14), // "timeoutConnect"
QT_MOC_LITERAL(4, 45, 13), // "backupConnect"
QT_MOC_LITERAL(5, 59, 9), // "sendHeart"
QT_MOC_LITERAL(6, 69, 12), // "restartHeart"
QT_MOC_LITERAL(7, 82, 15), // "setTimeoutHeart"
QT_MOC_LITERAL(8, 98, 17) // "setTimeoutConnect"

    },
    "WLModuleConnect\0timeoutHeart\0\0"
    "timeoutConnect\0backupConnect\0sendHeart\0"
    "restartHeart\0setTimeoutHeart\0"
    "setTimeoutConnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLModuleConnect[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WLModuleConnect::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLModuleConnect *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->timeoutHeart(); break;
        case 1: _t->timeoutConnect(); break;
        case 2: _t->backupConnect(); break;
        case 3: _t->sendHeart(); break;
        case 4: _t->restartHeart(); break;
        case 5: _t->setTimeoutHeart(); break;
        case 6: _t->setTimeoutConnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLModuleConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleConnect::timeoutHeart)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLModuleConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleConnect::timeoutConnect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLModuleConnect::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleConnect::backupConnect)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject WLModuleConnect::staticMetaObject = { {
    &WLModule::staticMetaObject,
    qt_meta_stringdata_WLModuleConnect.data,
    qt_meta_data_WLModuleConnect,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLModuleConnect::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLModuleConnect::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLModuleConnect.stringdata0))
        return static_cast<void*>(this);
    return WLModule::qt_metacast(_clname);
}

int WLModuleConnect::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WLModule::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void WLModuleConnect::timeoutHeart()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WLModuleConnect::timeoutConnect()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WLModuleConnect::backupConnect()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
