/****************************************************************************
** Meta object code from reading C++ file 'WLModuleIOPUT.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../WLMotion/modules/WLModuleIOPUT.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WLModuleIOPUT.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLModuleIOPut_t {
    QByteArrayData data[25];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLModuleIOPut_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLModuleIOPut_t qt_meta_stringdata_WLModuleIOPut = {
    {
QT_MOC_LITERAL(0, 0, 13), // "WLModuleIOPut"
QT_MOC_LITERAL(1, 14, 11), // "outputSetTo"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "index"
QT_MOC_LITERAL(4, 33, 3), // "out"
QT_MOC_LITERAL(5, 37, 9), // "outputSet"
QT_MOC_LITERAL(6, 47, 11), // "outputReset"
QT_MOC_LITERAL(7, 59, 9), // "outputTog"
QT_MOC_LITERAL(8, 69, 19), // "sendGetAllInputData"
QT_MOC_LITERAL(9, 89, 20), // "sendGetAllOutputData"
QT_MOC_LITERAL(10, 110, 12), // "sendSetOData"
QT_MOC_LITERAL(11, 123, 3), // "all"
QT_MOC_LITERAL(12, 127, 5), // "input"
QT_MOC_LITERAL(13, 133, 4), // "byte"
QT_MOC_LITERAL(14, 138, 3), // "in7"
QT_MOC_LITERAL(15, 142, 3), // "in6"
QT_MOC_LITERAL(16, 146, 3), // "in5"
QT_MOC_LITERAL(17, 150, 3), // "in4"
QT_MOC_LITERAL(18, 154, 3), // "in3"
QT_MOC_LITERAL(19, 158, 3), // "in2"
QT_MOC_LITERAL(20, 162, 3), // "in1"
QT_MOC_LITERAL(21, 166, 3), // "in0"
QT_MOC_LITERAL(22, 170, 10), // "otputPulse"
QT_MOC_LITERAL(23, 181, 4), // "time"
QT_MOC_LITERAL(24, 186, 6) // "output"

    },
    "WLModuleIOPut\0outputSetTo\0\0index\0out\0"
    "outputSet\0outputReset\0outputTog\0"
    "sendGetAllInputData\0sendGetAllOutputData\0"
    "sendSetOData\0all\0input\0byte\0in7\0in6\0"
    "in5\0in4\0in3\0in2\0in1\0in0\0otputPulse\0"
    "time\0output"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLModuleIOPut[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x0a /* Public */,
       5,    1,   79,    2, 0x0a /* Public */,
       6,    1,   82,    2, 0x0a /* Public */,
       7,    1,   85,    2, 0x0a /* Public */,
       8,    0,   88,    2, 0x08 /* Private */,
       9,    0,   89,    2, 0x08 /* Private */,
      10,    1,   90,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x28 /* Private | MethodCloned */,

 // methods: name, argc, parameters, tag, flags
      12,    1,   94,    2, 0x02 /* Public */,
      13,    8,   97,    2, 0x02 /* Public */,
      22,    3,  114,    2, 0x02 /* Public */,
      24,    1,  121,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Bool, QMetaType::Int,    3,
    QMetaType::UChar, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,   14,   15,   16,   17,   18,   19,   20,   21,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::Int,    3,    4,   23,
    QMetaType::Bool, QMetaType::Int,    3,

       0        // eod
};

void WLModuleIOPut::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLModuleIOPut *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->outputSetTo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->outputSet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->outputReset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->outputTog((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->sendGetAllInputData(); break;
        case 5: _t->sendGetAllOutputData(); break;
        case 6: _t->sendSetOData((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->sendSetOData(); break;
        case 8: { bool _r = _t->input((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: { quint8 _r = _t->byte((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7])),(*reinterpret_cast< int(*)>(_a[8])));
            if (_a[0]) *reinterpret_cast< quint8*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->otputPulse((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: { bool _r = _t->output((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLModuleIOPut::staticMetaObject = { {
    &WLModule::staticMetaObject,
    qt_meta_stringdata_WLModuleIOPut.data,
    qt_meta_data_WLModuleIOPut,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLModuleIOPut::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLModuleIOPut::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLModuleIOPut.stringdata0))
        return static_cast<void*>(this);
    return WLModule::qt_metacast(_clname);
}

int WLModuleIOPut::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = WLModule::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
