/****************************************************************************
** Meta object code from reading C++ file 'wlaxis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlmotion/modules/wlaxis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlaxis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLAxis_t {
    QByteArrayData data[14];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLAxis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLAxis_t qt_meta_stringdata_WLAxis = {
    {
QT_MOC_LITERAL(0, 0, 6), // "WLAxis"
QT_MOC_LITERAL(1, 7, 13), // "changedLatch2"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "changedLatch3"
QT_MOC_LITERAL(4, 36, 12), // "changedError"
QT_MOC_LITERAL(5, 49, 15), // "changedPosition"
QT_MOC_LITERAL(6, 65, 13), // "changedStatus"
QT_MOC_LITERAL(7, 79, 10), // "statusAxis"
QT_MOC_LITERAL(8, 90, 11), // "changedMode"
QT_MOC_LITERAL(9, 102, 8), // "modeAxis"
QT_MOC_LITERAL(10, 111, 11), // "changedFreq"
QT_MOC_LITERAL(11, 123, 12), // "changedInALM"
QT_MOC_LITERAL(12, 136, 8), // "finished"
QT_MOC_LITERAL(13, 145, 7) // "started"

    },
    "WLAxis\0changedLatch2\0\0changedLatch3\0"
    "changedError\0changedPosition\0changedStatus\0"
    "statusAxis\0changedMode\0modeAxis\0"
    "changedFreq\0changedInALM\0finished\0"
    "started"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLAxis[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       3,    1,   67,    2, 0x06 /* Public */,
       4,    1,   70,    2, 0x06 /* Public */,
       5,    1,   73,    2, 0x06 /* Public */,
       6,    1,   76,    2, 0x06 /* Public */,
       8,    1,   79,    2, 0x06 /* Public */,
      10,    1,   82,    2, 0x06 /* Public */,
      11,    1,   85,    2, 0x06 /* Public */,
      12,    0,   88,    2, 0x06 /* Public */,
      13,    0,   89,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::UChar,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WLAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLAxis *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changedLatch2((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 1: _t->changedLatch3((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->changedError((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->changedPosition((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->changedStatus((*reinterpret_cast< statusAxis(*)>(_a[1]))); break;
        case 5: _t->changedMode((*reinterpret_cast< modeAxis(*)>(_a[1]))); break;
        case 6: _t->changedFreq((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 7: _t->changedInALM((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->finished(); break;
        case 9: _t->started(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLAxis::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::changedLatch2)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::changedLatch3)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::changedError)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::changedPosition)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(statusAxis );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::changedStatus)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(modeAxis );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::changedMode)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::changedFreq)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::changedInALM)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::finished)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::started)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLAxis::staticMetaObject = { {
    &WLElement::staticMetaObject,
    qt_meta_stringdata_WLAxis.data,
    qt_meta_data_WLAxis,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLAxis.stringdata0))
        return static_cast<void*>(this);
    return WLElement::qt_metacast(_clname);
}

int WLAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WLElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void WLAxis::changedLatch2(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLAxis::changedLatch3(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WLAxis::changedError(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WLAxis::changedPosition(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WLAxis::changedStatus(statusAxis _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WLAxis::changedMode(modeAxis _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void WLAxis::changedFreq(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void WLAxis::changedInALM(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void WLAxis::finished()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void WLAxis::started()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
