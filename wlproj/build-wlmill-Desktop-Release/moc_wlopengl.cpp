/****************************************************************************
** Meta object code from reading C++ file 'wlopengl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../wlqt/wlopengl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlopengl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLOpenGL_t {
    QByteArrayData data[12];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLOpenGL_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLOpenGL_t qt_meta_stringdata_WLOpenGL = {
    {
QT_MOC_LITERAL(0, 0, 8), // "WLOpenGL"
QT_MOC_LITERAL(1, 9, 10), // "updateView"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 13), // "setClearColor"
QT_MOC_LITERAL(4, 35, 6), // "_color"
QT_MOC_LITERAL(5, 42, 9), // "setViewUp"
QT_MOC_LITERAL(6, 52, 11), // "setViewDown"
QT_MOC_LITERAL(7, 64, 11), // "setViewLeft"
QT_MOC_LITERAL(8, 76, 12), // "setViewRight"
QT_MOC_LITERAL(9, 89, 12), // "setViewFront"
QT_MOC_LITERAL(10, 102, 11), // "setViewRear"
QT_MOC_LITERAL(11, 114, 13) // "setViewCenter"

    },
    "WLOpenGL\0updateView\0\0setClearColor\0"
    "_color\0setViewUp\0setViewDown\0setViewLeft\0"
    "setViewRight\0setViewFront\0setViewRear\0"
    "setViewCenter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLOpenGL[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    1,   60,    2, 0x0a /* Public */,
       5,    0,   63,    2, 0x0a /* Public */,
       6,    0,   64,    2, 0x0a /* Public */,
       7,    0,   65,    2, 0x0a /* Public */,
       8,    0,   66,    2, 0x0a /* Public */,
       9,    0,   67,    2, 0x0a /* Public */,
      10,    0,   68,    2, 0x0a /* Public */,
      11,    0,   69,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void WLOpenGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLOpenGL *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateView(); break;
        case 1: _t->setClearColor((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 2: _t->setViewUp(); break;
        case 3: _t->setViewDown(); break;
        case 4: _t->setViewLeft(); break;
        case 5: _t->setViewRight(); break;
        case 6: _t->setViewFront(); break;
        case 7: _t->setViewRear(); break;
        case 8: _t->setViewCenter(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLOpenGL::staticMetaObject = { {
    &QOpenGLWidget::staticMetaObject,
    qt_meta_stringdata_WLOpenGL.data,
    qt_meta_data_WLOpenGL,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLOpenGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLOpenGL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLOpenGL.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions"))
        return static_cast< QOpenGLFunctions*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int WLOpenGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
