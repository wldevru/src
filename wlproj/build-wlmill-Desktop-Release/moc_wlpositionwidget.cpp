/****************************************************************************
** Meta object code from reading C++ file 'wlpositionwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wlmill/wlpositionwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wlpositionwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLPositionWidget_t {
    QByteArrayData data[31];
    char stringdata0[319];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLPositionWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLPositionWidget_t qt_meta_stringdata_WLPositionWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "WLPositionWidget"
QT_MOC_LITERAL(1, 17, 13), // "changedViewSC"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 19), // "changedHomePosition"
QT_MOC_LITERAL(4, 52, 7), // "WLFrame"
QT_MOC_LITERAL(5, 60, 9), // "onExGCode"
QT_MOC_LITERAL(6, 70, 17), // "updateEnableMoved"
QT_MOC_LITERAL(7, 88, 10), // "onPBSetXY0"
QT_MOC_LITERAL(8, 99, 9), // "onPBRotSK"
QT_MOC_LITERAL(9, 109, 11), // "onPBsetHome"
QT_MOC_LITERAL(10, 121, 11), // "onPBgetHome"
QT_MOC_LITERAL(11, 133, 9), // "onPBsetP0"
QT_MOC_LITERAL(12, 143, 9), // "onPBsetP1"
QT_MOC_LITERAL(13, 153, 11), // "setPosition"
QT_MOC_LITERAL(14, 165, 9), // "nameDrive"
QT_MOC_LITERAL(15, 175, 3), // "pos"
QT_MOC_LITERAL(16, 179, 4), // "type"
QT_MOC_LITERAL(17, 184, 8), // "onPBsetX"
QT_MOC_LITERAL(18, 193, 8), // "onPBsetY"
QT_MOC_LITERAL(19, 202, 8), // "onPBsetZ"
QT_MOC_LITERAL(20, 211, 8), // "onPBsetA"
QT_MOC_LITERAL(21, 220, 8), // "onPBsetB"
QT_MOC_LITERAL(22, 229, 8), // "onPBGoTo"
QT_MOC_LITERAL(23, 238, 10), // "onSetDrive"
QT_MOC_LITERAL(24, 249, 8), // "onGoHome"
QT_MOC_LITERAL(25, 258, 9), // "onPBRotSC"
QT_MOC_LITERAL(26, 268, 15), // "setEditDisabled"
QT_MOC_LITERAL(27, 284, 3), // "dis"
QT_MOC_LITERAL(28, 288, 14), // "updatePosition"
QT_MOC_LITERAL(29, 303, 9), // "setViewSC"
QT_MOC_LITERAL(30, 313, 5) // "index"

    },
    "WLPositionWidget\0changedViewSC\0\0"
    "changedHomePosition\0WLFrame\0onExGCode\0"
    "updateEnableMoved\0onPBSetXY0\0onPBRotSK\0"
    "onPBsetHome\0onPBgetHome\0onPBsetP0\0"
    "onPBsetP1\0setPosition\0nameDrive\0pos\0"
    "type\0onPBsetX\0onPBsetY\0onPBsetZ\0"
    "onPBsetA\0onPBsetB\0onPBGoTo\0onSetDrive\0"
    "onGoHome\0onPBRotSC\0setEditDisabled\0"
    "dis\0updatePosition\0setViewSC\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLPositionWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  129,    2, 0x06 /* Public */,
       3,    1,  132,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  135,    2, 0x08 /* Private */,
       6,    1,  136,    2, 0x08 /* Private */,
       7,    0,  139,    2, 0x08 /* Private */,
       8,    0,  140,    2, 0x08 /* Private */,
       9,    0,  141,    2, 0x08 /* Private */,
      10,    0,  142,    2, 0x08 /* Private */,
      11,    0,  143,    2, 0x08 /* Private */,
      12,    0,  144,    2, 0x08 /* Private */,
      13,    3,  145,    2, 0x08 /* Private */,
      17,    1,  152,    2, 0x08 /* Private */,
      18,    1,  155,    2, 0x08 /* Private */,
      19,    1,  158,    2, 0x08 /* Private */,
      20,    1,  161,    2, 0x08 /* Private */,
      21,    1,  164,    2, 0x08 /* Private */,
      22,    0,  167,    2, 0x08 /* Private */,
      23,    2,  168,    2, 0x08 /* Private */,
      24,    0,  173,    2, 0x0a /* Public */,
      25,    0,  174,    2, 0x0a /* Public */,
      26,    1,  175,    2, 0x0a /* Public */,
      28,    0,  178,    2, 0x0a /* Public */,
      29,    1,  179,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Float, QMetaType::Int,   14,   15,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   14,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   27,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   30,

       0        // eod
};

void WLPositionWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLPositionWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changedViewSC((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->changedHomePosition((*reinterpret_cast< WLFrame(*)>(_a[1]))); break;
        case 2: _t->onExGCode(); break;
        case 3: _t->updateEnableMoved((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->onPBSetXY0(); break;
        case 5: _t->onPBRotSK(); break;
        case 6: _t->onPBsetHome(); break;
        case 7: _t->onPBgetHome(); break;
        case 8: _t->onPBsetP0(); break;
        case 9: _t->onPBsetP1(); break;
        case 10: _t->setPosition((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 11: _t->onPBsetX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->onPBsetY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->onPBsetZ((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->onPBsetA((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->onPBsetB((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->onPBGoTo(); break;
        case 17: _t->onSetDrive((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 18: _t->onGoHome(); break;
        case 19: _t->onPBRotSC(); break;
        case 20: _t->setEditDisabled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->updatePosition(); break;
        case 22: _t->setViewSC((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLPositionWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLPositionWidget::changedViewSC)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLPositionWidget::*)(WLFrame );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLPositionWidget::changedHomePosition)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLPositionWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_WLPositionWidget.data,
    qt_meta_data_WLPositionWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLPositionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLPositionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLPositionWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WLPositionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 23)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 23;
    }
    return _id;
}

// SIGNAL 0
void WLPositionWidget::changedViewSC(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLPositionWidget::changedHomePosition(WLFrame _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
