/****************************************************************************
** Meta object code from reading C++ file 'wlgprogramwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlqt/form/wlgprogramwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlgprogramwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLGProgramWidget_t {
    QByteArrayData data[16];
    char stringdata0[222];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLGProgramWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLGProgramWidget_t qt_meta_stringdata_WLGProgramWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "WLGProgramWidget"
QT_MOC_LITERAL(1, 17, 7), // "changed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 18), // "changedEditElement"
QT_MOC_LITERAL(4, 45, 5), // "index"
QT_MOC_LITERAL(5, 51, 15), // "setEditDisabled"
QT_MOC_LITERAL(6, 67, 14), // "setEditElement"
QT_MOC_LITERAL(7, 82, 8), // "iElement"
QT_MOC_LITERAL(8, 91, 15), // "loadTextProgram"
QT_MOC_LITERAL(9, 107, 8), // "onUpdate"
QT_MOC_LITERAL(10, 116, 8), // "onAccept"
QT_MOC_LITERAL(11, 125, 8), // "onBackup"
QT_MOC_LITERAL(12, 134, 8), // "onReload"
QT_MOC_LITERAL(13, 143, 20), // "onChangedTextProgram"
QT_MOC_LITERAL(14, 164, 28), // "onChangedPositionTextProgram"
QT_MOC_LITERAL(15, 193, 28) // "onChangedPositionListProgram"

    },
    "WLGProgramWidget\0changed\0\0changedEditElement\0"
    "index\0setEditDisabled\0setEditElement\0"
    "iElement\0loadTextProgram\0onUpdate\0"
    "onAccept\0onBackup\0onReload\0"
    "onChangedTextProgram\0onChangedPositionTextProgram\0"
    "onChangedPositionListProgram"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLGProgramWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       3,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   80,    2, 0x0a /* Public */,
       6,    1,   83,    2, 0x0a /* Public */,
       8,    0,   86,    2, 0x0a /* Public */,
       9,    0,   87,    2, 0x08 /* Private */,
      10,    0,   88,    2, 0x08 /* Private */,
      11,    0,   89,    2, 0x08 /* Private */,
      12,    0,   90,    2, 0x08 /* Private */,
      13,    0,   91,    2, 0x08 /* Private */,
      14,    0,   92,    2, 0x08 /* Private */,
      15,    0,   93,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WLGProgramWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLGProgramWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changed((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->changedEditElement((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setEditDisabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->setEditElement((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->loadTextProgram(); break;
        case 5: _t->onUpdate(); break;
        case 6: _t->onAccept(); break;
        case 7: _t->onBackup(); break;
        case 8: _t->onReload(); break;
        case 9: _t->onChangedTextProgram(); break;
        case 10: _t->onChangedPositionTextProgram(); break;
        case 11: _t->onChangedPositionListProgram(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLGProgramWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLGProgramWidget::changed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLGProgramWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLGProgramWidget::changedEditElement)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLGProgramWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_WLGProgramWidget.data,
    qt_meta_data_WLGProgramWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLGProgramWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLGProgramWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLGProgramWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WLGProgramWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void WLGProgramWidget::changed(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLGProgramWidget::changedEditElement(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
