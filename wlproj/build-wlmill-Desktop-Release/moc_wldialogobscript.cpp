/****************************************************************************
** Meta object code from reading C++ file 'wldialogobscript.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wlmill/wldialogobscript.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wldialogobscript.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLDialogObj_t {
    QByteArrayData data[23];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLDialogObj_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLDialogObj_t qt_meta_stringdata_WLDialogObj = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WLDialogObj"
QT_MOC_LITERAL(1, 12, 12), // "buildMessage"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "buildEnterNum"
QT_MOC_LITERAL(4, 40, 16), // "buildEnterString"
QT_MOC_LITERAL(5, 57, 13), // "buildSaveFile"
QT_MOC_LITERAL(6, 71, 11), // "sendMessage"
QT_MOC_LITERAL(7, 83, 9), // "setString"
QT_MOC_LITERAL(8, 93, 3), // "str"
QT_MOC_LITERAL(9, 97, 6), // "setNum"
QT_MOC_LITERAL(10, 104, 3), // "num"
QT_MOC_LITERAL(11, 108, 9), // "setCancel"
QT_MOC_LITERAL(12, 118, 7), // "message"
QT_MOC_LITERAL(13, 126, 3), // "txt"
QT_MOC_LITERAL(14, 130, 8), // "enterNum"
QT_MOC_LITERAL(15, 139, 11), // "enterString"
QT_MOC_LITERAL(16, 151, 13), // "enterSaveFile"
QT_MOC_LITERAL(17, 165, 4), // "last"
QT_MOC_LITERAL(18, 170, 6), // "isShow"
QT_MOC_LITERAL(19, 177, 4), // "isOk"
QT_MOC_LITERAL(20, 182, 8), // "isCancel"
QT_MOC_LITERAL(21, 191, 6), // "getNum"
QT_MOC_LITERAL(22, 198, 9) // "getString"

    },
    "WLDialogObj\0buildMessage\0\0buildEnterNum\0"
    "buildEnterString\0buildSaveFile\0"
    "sendMessage\0setString\0str\0setNum\0num\0"
    "setCancel\0message\0txt\0enterNum\0"
    "enterString\0enterSaveFile\0last\0isShow\0"
    "isOk\0isCancel\0getNum\0getString"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLDialogObj[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       3,    1,  102,    2, 0x06 /* Public */,
       4,    1,  105,    2, 0x06 /* Public */,
       5,    2,  108,    2, 0x06 /* Public */,
       6,    3,  113,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,  120,    2, 0x0a /* Public */,
       9,    1,  123,    2, 0x0a /* Public */,
      11,    0,  126,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      12,    1,  127,    2, 0x02 /* Public */,
      14,    1,  130,    2, 0x02 /* Public */,
      15,    1,  133,    2, 0x02 /* Public */,
      16,    2,  136,    2, 0x02 /* Public */,
      18,    0,  141,    2, 0x02 /* Public */,
      19,    0,  142,    2, 0x02 /* Public */,
      20,    0,  143,    2, 0x02 /* Public */,
      21,    0,  144,    2, 0x02 /* Public */,
      22,    0,  145,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Double,   10,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   13,   17,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Double,
    QMetaType::QString,

       0        // eod
};

void WLDialogObj::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLDialogObj *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buildMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->buildEnterNum((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->buildEnterString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->buildSaveFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 5: _t->setString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->setNum((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 7: _t->setCancel(); break;
        case 8: _t->message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->enterNum((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->enterString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->enterSaveFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 12: { bool _r = _t->isShow();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { bool _r = _t->isOk();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 14: { bool _r = _t->isCancel();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 15: { double _r = _t->getNum();
            if (_a[0]) *reinterpret_cast< double*>(_a[0]) = std::move(_r); }  break;
        case 16: { QString _r = _t->getString();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLDialogObj::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDialogObj::buildMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLDialogObj::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDialogObj::buildEnterNum)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLDialogObj::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDialogObj::buildEnterString)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WLDialogObj::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDialogObj::buildSaveFile)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WLDialogObj::*)(QString , QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDialogObj::sendMessage)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLDialogObj::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_WLDialogObj.data,
    qt_meta_data_WLDialogObj,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLDialogObj::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLDialogObj::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLDialogObj.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WLDialogObj::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void WLDialogObj::buildMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLDialogObj::buildEnterNum(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WLDialogObj::buildEnterString(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void WLDialogObj::buildSaveFile(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WLDialogObj::sendMessage(QString _t1, QString _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
