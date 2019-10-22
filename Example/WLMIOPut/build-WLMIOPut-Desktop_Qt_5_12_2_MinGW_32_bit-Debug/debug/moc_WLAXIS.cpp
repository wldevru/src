/****************************************************************************
** Meta object code from reading C++ file 'WLAXIS.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../WLMotion/modules/WLAXIS.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WLAXIS.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLAxis_t {
    QByteArrayData data[11];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLAxis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLAxis_t qt_meta_stringdata_WLAxis = {
    {
QT_MOC_LITERAL(0, 0, 6), // "WLAxis"
QT_MOC_LITERAL(1, 7, 13), // "ChangedLatch2"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "ChangedLatch3"
QT_MOC_LITERAL(4, 36, 12), // "ChangedError"
QT_MOC_LITERAL(5, 49, 10), // "ChangedPos"
QT_MOC_LITERAL(6, 60, 13), // "ChangedStatus"
QT_MOC_LITERAL(7, 74, 10), // "statusAxis"
QT_MOC_LITERAL(8, 85, 11), // "ChangedMode"
QT_MOC_LITERAL(9, 97, 8), // "modeAxis"
QT_MOC_LITERAL(10, 106, 11) // "ChangedFreq"

    },
    "WLAxis\0ChangedLatch2\0\0ChangedLatch3\0"
    "ChangedError\0ChangedPos\0ChangedStatus\0"
    "statusAxis\0ChangedMode\0modeAxis\0"
    "ChangedFreq"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLAxis[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    1,   52,    2, 0x06 /* Public */,
       4,    1,   55,    2, 0x06 /* Public */,
       5,    1,   58,    2, 0x06 /* Public */,
       6,    1,   61,    2, 0x06 /* Public */,
       8,    1,   64,    2, 0x06 /* Public */,
      10,    1,   67,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::UChar,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, QMetaType::Float,    2,

       0        // eod
};

void WLAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLAxis *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ChangedLatch2((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 1: _t->ChangedLatch3((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 2: _t->ChangedError((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 3: _t->ChangedPos((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->ChangedStatus((*reinterpret_cast< statusAxis(*)>(_a[1]))); break;
        case 5: _t->ChangedMode((*reinterpret_cast< modeAxis(*)>(_a[1]))); break;
        case 6: _t->ChangedFreq((*reinterpret_cast< float(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLAxis::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::ChangedLatch2)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::ChangedLatch3)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::ChangedError)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::ChangedPos)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(statusAxis );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::ChangedStatus)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(modeAxis );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::ChangedMode)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (WLAxis::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAxis::ChangedFreq)) {
                *result = 6;
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
void WLAxis::ChangedLatch2(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLAxis::ChangedLatch3(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WLAxis::ChangedError(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WLAxis::ChangedPos(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WLAxis::ChangedStatus(statusAxis _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WLAxis::ChangedMode(modeAxis _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void WLAxis::ChangedFreq(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
