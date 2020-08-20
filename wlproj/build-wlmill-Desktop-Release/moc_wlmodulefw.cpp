/****************************************************************************
** Meta object code from reading C++ file 'wlmodulefw.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlmotion/modules/wlmodulefw.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlmodulefw.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLModuleFW_t {
    QByteArrayData data[10];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLModuleFW_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLModuleFW_t qt_meta_stringdata_WLModuleFW = {
    {
QT_MOC_LITERAL(0, 0, 10), // "WLModuleFW"
QT_MOC_LITERAL(1, 11, 11), // "sendMessage"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 14), // "changedConnect"
QT_MOC_LITERAL(4, 39, 11), // "changedProp"
QT_MOC_LITERAL(5, 51, 12), // "changedActiv"
QT_MOC_LITERAL(6, 64, 18), // "changedEndReadPage"
QT_MOC_LITERAL(7, 83, 9), // "endReadFW"
QT_MOC_LITERAL(8, 93, 10), // "endWriteFW"
QT_MOC_LITERAL(9, 104, 15) // "changedProgress"

    },
    "WLModuleFW\0sendMessage\0\0changedConnect\0"
    "changedProp\0changedActiv\0changedEndReadPage\0"
    "endReadFW\0endWriteFW\0changedProgress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLModuleFW[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x06 /* Public */,
       3,    1,   61,    2, 0x06 /* Public */,
       4,    1,   64,    2, 0x06 /* Public */,
       5,    1,   67,    2, 0x06 /* Public */,
       6,    0,   70,    2, 0x06 /* Public */,
       7,    0,   71,    2, 0x06 /* Public */,
       8,    0,   72,    2, 0x06 /* Public */,
       9,    1,   73,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void WLModuleFW::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLModuleFW *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->changedConnect((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->changedProp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->changedActiv((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->changedEndReadPage(); break;
        case 5: _t->endReadFW(); break;
        case 6: _t->endWriteFW(); break;
        case 7: _t->changedProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLModuleFW::*)(QString , QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleFW::sendMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLModuleFW::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleFW::changedConnect)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLModuleFW::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleFW::changedProp)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WLModuleFW::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleFW::changedActiv)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WLModuleFW::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleFW::changedEndReadPage)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WLModuleFW::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleFW::endReadFW)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (WLModuleFW::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleFW::endWriteFW)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (WLModuleFW::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleFW::changedProgress)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLModuleFW::staticMetaObject = { {
    &WLModule::staticMetaObject,
    qt_meta_stringdata_WLModuleFW.data,
    qt_meta_data_WLModuleFW,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLModuleFW::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLModuleFW::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLModuleFW.stringdata0))
        return static_cast<void*>(this);
    return WLModule::qt_metacast(_clname);
}

int WLModuleFW::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WLModule::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void WLModuleFW::sendMessage(QString _t1, QString _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLModuleFW::changedConnect(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WLModuleFW::changedProp(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WLModuleFW::changedActiv(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WLModuleFW::changedEndReadPage()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void WLModuleFW::endReadFW()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void WLModuleFW::endWriteFW()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void WLModuleFW::changedProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
