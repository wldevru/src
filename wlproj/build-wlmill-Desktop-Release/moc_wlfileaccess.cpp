/****************************************************************************
** Meta object code from reading C++ file 'wlfileaccess.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlqt/wlfileaccess.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlfileaccess.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLFileAccess_t {
    QByteArrayData data[11];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLFileAccess_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLFileAccess_t qt_meta_stringdata_WLFileAccess = {
    {
QT_MOC_LITERAL(0, 0, 12), // "WLFileAccess"
QT_MOC_LITERAL(1, 13, 7), // "loadVal"
QT_MOC_LITERAL(2, 21, 12), // "QScriptValue"
QT_MOC_LITERAL(3, 34, 0), // ""
QT_MOC_LITERAL(4, 35, 8), // "namefile"
QT_MOC_LITERAL(5, 44, 8), // "nameData"
QT_MOC_LITERAL(6, 53, 7), // "saveVal"
QT_MOC_LITERAL(7, 61, 4), // "data"
QT_MOC_LITERAL(8, 66, 10), // "createFile"
QT_MOC_LITERAL(9, 77, 5), // "write"
QT_MOC_LITERAL(10, 83, 3) // "str"

    },
    "WLFileAccess\0loadVal\0QScriptValue\0\0"
    "namefile\0nameData\0saveVal\0data\0"
    "createFile\0write\0str"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLFileAccess[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    2,   34,    3, 0x02 /* Public */,
       6,    3,   39,    3, 0x02 /* Public */,
       8,    1,   46,    3, 0x02 /* Public */,
       9,    2,   49,    3, 0x02 /* Public */,

 // methods: parameters
    0x80000000 | 2, QMetaType::QString, QMetaType::QString,    4,    5,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, 0x80000000 | 2,    4,    5,    7,
    QMetaType::Bool, QMetaType::QString,    4,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString,    4,   10,

       0        // eod
};

void WLFileAccess::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLFileAccess *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: { QScriptValue _r = _t->loadVal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QScriptValue*>(_a[0]) = std::move(_r); }  break;
        case 1: { bool _r = _t->saveVal((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QScriptValue(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->createFile((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: { bool _r = _t->write((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLFileAccess::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WLFileAccess.data,
    qt_meta_data_WLFileAccess,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLFileAccess::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLFileAccess::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLFileAccess.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WLFileAccess::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
