/****************************************************************************
** Meta object code from reading C++ file 'wllabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlqt/wllabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wllabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLLabel_t {
    QByteArrayData data[10];
    char stringdata0[53];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLLabel_t qt_meta_stringdata_WLLabel = {
    {
QT_MOC_LITERAL(0, 0, 7), // "WLLabel"
QT_MOC_LITERAL(1, 8, 8), // "dclicked"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 8), // "setDataD"
QT_MOC_LITERAL(4, 27, 1), // "d"
QT_MOC_LITERAL(5, 29, 7), // "setData"
QT_MOC_LITERAL(6, 37, 1), // "l"
QT_MOC_LITERAL(7, 39, 1), // "i"
QT_MOC_LITERAL(8, 41, 7), // "setText"
QT_MOC_LITERAL(9, 49, 3) // "txt"

    },
    "WLLabel\0dclicked\0\0setDataD\0d\0setData\0"
    "l\0i\0setText\0txt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLLabel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   45,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       5,    1,   51,    2, 0x0a /* Public */,
       5,    1,   54,    2, 0x0a /* Public */,
       8,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Double,    4,
    QMetaType::Void, QMetaType::Float,    4,
    QMetaType::Void, QMetaType::Long,    6,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void WLLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->dclicked(); break;
        case 1: _t->setDataD((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->setData((*reinterpret_cast< float(*)>(_a[1]))); break;
        case 3: _t->setData((*reinterpret_cast< long(*)>(_a[1]))); break;
        case 4: _t->setData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLLabel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLLabel::dclicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLLabel::staticMetaObject = { {
    &QLabel::staticMetaObject,
    qt_meta_stringdata_WLLabel.data,
    qt_meta_data_WLLabel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLLabel.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int WLLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void WLLabel::dclicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
