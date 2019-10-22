/****************************************************************************
** Meta object code from reading C++ file 'WLModuleAxis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../WLMotion/modules/WLModuleAxis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WLModuleAxis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLModuleAxis_t {
    QByteArrayData data[12];
    char stringdata0[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLModuleAxis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLModuleAxis_t qt_meta_stringdata_WLModuleAxis = {
    {
QT_MOC_LITERAL(0, 0, 12), // "WLModuleAxis"
QT_MOC_LITERAL(1, 13, 16), // "changedInEMGStop"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "setLatchProbe2"
QT_MOC_LITERAL(4, 46, 7), // "qint32*"
QT_MOC_LITERAL(5, 54, 3), // "Pos"
QT_MOC_LITERAL(6, 58, 14), // "setLatchProbe3"
QT_MOC_LITERAL(7, 73, 12), // "callDataAxis"
QT_MOC_LITERAL(8, 86, 7), // "getFmax"
QT_MOC_LITERAL(9, 94, 14), // "getLatchProbe2"
QT_MOC_LITERAL(10, 109, 5), // "index"
QT_MOC_LITERAL(11, 115, 14) // "getLatchProbe3"

    },
    "WLModuleAxis\0changedInEMGStop\0\0"
    "setLatchProbe2\0qint32*\0Pos\0setLatchProbe3\0"
    "callDataAxis\0getFmax\0getLatchProbe2\0"
    "index\0getLatchProbe3"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLModuleAxis[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   52,    2, 0x08 /* Private */,
       6,    2,   57,    2, 0x08 /* Private */,
       7,    0,   62,    2, 0x08 /* Private */,

 // methods: name, argc, parameters, tag, flags
       8,    0,   63,    2, 0x02 /* Public */,
       9,    1,   64,    2, 0x02 /* Public */,
      11,    1,   67,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, QMetaType::UChar,    5,    2,
    QMetaType::Void, 0x80000000 | 4, QMetaType::UChar,    5,    2,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Float,
    QMetaType::Double, QMetaType::Int,   10,
    QMetaType::Double, QMetaType::Int,   10,

       0        // eod
};

void WLModuleAxis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLModuleAxis *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changedInEMGStop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setLatchProbe2((*reinterpret_cast< qint32*(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 2: _t->setLatchProbe3((*reinterpret_cast< qint32*(*)>(_a[1])),(*reinterpret_cast< quint8(*)>(_a[2]))); break;
        case 3: _t->callDataAxis(); break;
        case 4: { float _r = _t->getFmax();
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 5: { double _r = _t->getLatchProbe2((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 6: { double _r = _t->getLatchProbe3((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLModuleAxis::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLModuleAxis::changedInEMGStop)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLModuleAxis::staticMetaObject = { {
    &WLModule::staticMetaObject,
    qt_meta_stringdata_WLModuleAxis.data,
    qt_meta_data_WLModuleAxis,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLModuleAxis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLModuleAxis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLModuleAxis.stringdata0))
        return static_cast<void*>(this);
    return WLModule::qt_metacast(_clname);
}

int WLModuleAxis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void WLModuleAxis::changedInEMGStop(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
