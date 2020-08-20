/****************************************************************************
** Meta object code from reading C++ file 'wlevscript.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wlmill/wlevscript.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlevscript.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLEVScript_t {
    QByteArrayData data[12];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLEVScript_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLEVScript_t qt_meta_stringdata_WLEVScript = {
    {
QT_MOC_LITERAL(0, 0, 10), // "WLEVScript"
QT_MOC_LITERAL(1, 11, 8), // "complete"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "changedBusy"
QT_MOC_LITERAL(4, 33, 11), // "sendMessage"
QT_MOC_LITERAL(5, 45, 5), // "reset"
QT_MOC_LITERAL(6, 51, 8), // "evalCode"
QT_MOC_LITERAL(7, 60, 8), // "evalFunc"
QT_MOC_LITERAL(8, 69, 4), // "eval"
QT_MOC_LITERAL(9, 74, 10), // "setMessage"
QT_MOC_LITERAL(10, 85, 3), // "txt"
QT_MOC_LITERAL(11, 89, 4) // "code"

    },
    "WLEVScript\0complete\0\0changedBusy\0"
    "sendMessage\0reset\0evalCode\0evalFunc\0"
    "eval\0setMessage\0txt\0code"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLEVScript[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    1,   57,    2, 0x06 /* Public */,
       4,    3,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    2,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   10,   11,

       0        // eod
};

void WLEVScript::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLEVScript *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->complete((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->changedBusy((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->reset(); break;
        case 4: _t->evalCode(); break;
        case 5: _t->evalFunc(); break;
        case 6: _t->eval(); break;
        case 7: _t->setMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLEVScript::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLEVScript::complete)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLEVScript::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLEVScript::changedBusy)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLEVScript::*)(QString , QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLEVScript::sendMessage)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLEVScript::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_WLEVScript.data,
    qt_meta_data_WLEVScript,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLEVScript::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLEVScript::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLEVScript.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int WLEVScript::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void WLEVScript::complete(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLEVScript::changedBusy(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WLEVScript::sendMessage(QString _t1, QString _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
