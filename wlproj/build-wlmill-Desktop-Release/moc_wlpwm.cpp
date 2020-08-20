/****************************************************************************
** Meta object code from reading C++ file 'wlpwm.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlmotion/modules/wlpwm.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlpwm.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLPWM_t {
    QByteArrayData data[8];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLPWM_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLPWM_t qt_meta_stringdata_WLPWM = {
    {
QT_MOC_LITERAL(0, 0, 5), // "WLPWM"
QT_MOC_LITERAL(1, 6, 12), // "changedError"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 11), // "changedFreq"
QT_MOC_LITERAL(4, 32, 12), // "changedPower"
QT_MOC_LITERAL(5, 45, 8), // "changedK"
QT_MOC_LITERAL(6, 54, 7), // "changed"
QT_MOC_LITERAL(7, 62, 4) // "kout"

    },
    "WLPWM\0changedError\0\0changedFreq\0"
    "changedPower\0changedK\0changed\0kout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLPWM[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       1,   52, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,
       4,    1,   45,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,
       6,    0,   51,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::Float, 0x00095002,

       0        // eod
};

void WLPWM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLPWM *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changedError((*reinterpret_cast< quint8(*)>(_a[1]))); break;
        case 1: _t->changedFreq((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->changedPower((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->changedK((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 4: _t->changed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLPWM::*)(quint8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLPWM::changedError)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLPWM::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLPWM::changedFreq)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLPWM::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLPWM::changedPower)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WLPWM::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLPWM::changedK)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WLPWM::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLPWM::changed)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<WLPWM *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setKOut(*reinterpret_cast< float*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject WLPWM::staticMetaObject = { {
    &WLElement::staticMetaObject,
    qt_meta_stringdata_WLPWM.data,
    qt_meta_data_WLPWM,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLPWM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLPWM::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLPWM.stringdata0))
        return static_cast<void*>(this);
    return WLElement::qt_metacast(_clname);
}

int WLPWM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WLElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void WLPWM::changedError(quint8 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLPWM::changedFreq(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WLPWM::changedPower(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WLPWM::changedK(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WLPWM::changed()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
