/****************************************************************************
** Meta object code from reading C++ file 'wlioput.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlmotion/modules/wlioput.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlioput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLIOPut_t {
    QByteArrayData data[16];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLIOPut_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLIOPut_t qt_meta_stringdata_WLIOPut = {
    {
QT_MOC_LITERAL(0, 0, 7), // "WLIOPut"
QT_MOC_LITERAL(1, 8, 7), // "changed"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 12), // "changedState"
QT_MOC_LITERAL(4, 30, 10), // "invChanged"
QT_MOC_LITERAL(5, 41, 10), // "setOutTogg"
QT_MOC_LITERAL(6, 52, 6), // "setNow"
QT_MOC_LITERAL(7, 59, 4), // "_now"
QT_MOC_LITERAL(8, 64, 6), // "setOut"
QT_MOC_LITERAL(9, 71, 3), // "now"
QT_MOC_LITERAL(10, 75, 11), // "setOutPulse"
QT_MOC_LITERAL(11, 87, 7), // "time_ms"
QT_MOC_LITERAL(12, 95, 11), // "setTogPulse"
QT_MOC_LITERAL(13, 107, 6), // "setTog"
QT_MOC_LITERAL(14, 114, 3), // "inv"
QT_MOC_LITERAL(15, 118, 3) // "out"

    },
    "WLIOPut\0changed\0\0changedState\0invChanged\0"
    "setOutTogg\0setNow\0_now\0setOut\0now\0"
    "setOutPulse\0time_ms\0setTogPulse\0setTog\0"
    "inv\0out"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLIOPut[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       3,   86, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       3,    2,   62,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   70,    2, 0x08 /* Private */,
       6,    1,   71,    2, 0x0a /* Public */,
       8,    1,   74,    2, 0x0a /* Public */,
      10,    2,   77,    2, 0x0a /* Public */,
      12,    1,   82,    2, 0x0a /* Public */,
      13,    0,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool, QMetaType::UInt,    7,   11,
    QMetaType::Void, QMetaType::UInt,   11,
    QMetaType::Void,

 // properties: name, type, flags
      14, QMetaType::Bool, 0x00495103,
       9, QMetaType::Bool, 0x00495001,
      15, QMetaType::Bool, 0x00095103,

 // properties: notify_signal_id
       2,
       0,
       0,

       0        // eod
};

void WLIOPut::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLIOPut *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->changedState((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->invChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setOutTogg(); break;
        case 4: _t->setNow((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setOut((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setOutPulse((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< quint32(*)>(_a[2]))); break;
        case 7: _t->setTogPulse((*reinterpret_cast< quint32(*)>(_a[1]))); break;
        case 8: _t->setTog(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLIOPut::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLIOPut::changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLIOPut::*)(int , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLIOPut::changedState)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLIOPut::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLIOPut::invChanged)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<WLIOPut *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< bool*>(_v) = _t->isInv(); break;
        case 1: *reinterpret_cast< bool*>(_v) = _t->getNow(); break;
        case 2: *reinterpret_cast< bool*>(_v) = _t->getNow(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<WLIOPut *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setInv(*reinterpret_cast< bool*>(_v)); break;
        case 2: _t->setOut(*reinterpret_cast< bool*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject WLIOPut::staticMetaObject = { {
    &WLElement::staticMetaObject,
    qt_meta_stringdata_WLIOPut.data,
    qt_meta_data_WLIOPut,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLIOPut::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLIOPut::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLIOPut.stringdata0))
        return static_cast<void*>(this);
    return WLElement::qt_metacast(_clname);
}

int WLIOPut::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WLElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WLIOPut::changed(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLIOPut::changedState(int _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WLIOPut::invChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
