/****************************************************************************
** Meta object code from reading C++ file 'wlaioput.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlmotion/modules/wlaioput.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlaioput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLAIOPut_t {
    QByteArrayData data[5];
    char stringdata0[51];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLAIOPut_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLAIOPut_t qt_meta_stringdata_WLAIOPut = {
    {
QT_MOC_LITERAL(0, 0, 8), // "WLAIOPut"
QT_MOC_LITERAL(1, 9, 12), // "changedValue"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 16), // "changedHistValue"
QT_MOC_LITERAL(4, 40, 10) // "changedInv"

    },
    "WLAIOPut\0changedValue\0\0changedHistValue\0"
    "changedInv"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLAIOPut[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       3,    1,   32,    2, 0x06 /* Public */,
       4,    1,   35,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Float,    2,
    QMetaType::Void, QMetaType::Bool,    2,

       0        // eod
};

void WLAIOPut::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLAIOPut *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changedValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 1: _t->changedHistValue((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 2: _t->changedInv((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLAIOPut::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAIOPut::changedValue)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLAIOPut::*)(float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAIOPut::changedHistValue)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLAIOPut::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLAIOPut::changedInv)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLAIOPut::staticMetaObject = { {
    &WLElement::staticMetaObject,
    qt_meta_stringdata_WLAIOPut.data,
    qt_meta_data_WLAIOPut,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLAIOPut::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLAIOPut::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLAIOPut.stringdata0))
        return static_cast<void*>(this);
    return WLElement::qt_metacast(_clname);
}

int WLAIOPut::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WLElement::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void WLAIOPut::changedValue(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLAIOPut::changedHistValue(float _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WLAIOPut::changedInv(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
