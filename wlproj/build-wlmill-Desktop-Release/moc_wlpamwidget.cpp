/****************************************************************************
** Meta object code from reading C++ file 'wlpamwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlqt/form/wlpamwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlpamwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLPamWidget_t {
    QByteArrayData data[12];
    char stringdata0[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLPamWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLPamWidget_t qt_meta_stringdata_WLPamWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "WLPamWidget"
QT_MOC_LITERAL(1, 12, 16), // "updateAccelLabel"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "index"
QT_MOC_LITERAL(4, 36, 14), // "updateVstLabel"
QT_MOC_LITERAL(5, 51, 3), // "val"
QT_MOC_LITERAL(6, 55, 14), // "updateVmaLabel"
QT_MOC_LITERAL(7, 70, 8), // "onAccept"
QT_MOC_LITERAL(8, 79, 8), // "onReject"
QT_MOC_LITERAL(9, 88, 18), // "setEnabledEditName"
QT_MOC_LITERAL(10, 107, 6), // "enable"
QT_MOC_LITERAL(11, 114, 17) // "setEnabledEditVst"

    },
    "WLPamWidget\0updateAccelLabel\0\0index\0"
    "updateVstLabel\0val\0updateVmaLabel\0"
    "onAccept\0onReject\0setEnabledEditName\0"
    "enable\0setEnabledEditVst"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLPamWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       4,    1,   52,    2, 0x08 /* Private */,
       6,    1,   55,    2, 0x08 /* Private */,
       7,    0,   58,    2, 0x08 /* Private */,
       8,    0,   59,    2, 0x08 /* Private */,
       9,    1,   60,    2, 0x0a /* Public */,
      11,    1,   63,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void, QMetaType::Double,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Bool,   10,

       0        // eod
};

void WLPamWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLPamWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateAccelLabel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateVstLabel((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 2: _t->updateVmaLabel((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 3: _t->onAccept(); break;
        case 4: _t->onReject(); break;
        case 5: _t->setEnabledEditName((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->setEnabledEditVst((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLPamWidget::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_WLPamWidget.data,
    qt_meta_data_WLPamWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLPamWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLPamWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLPamWidget.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int WLPamWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
