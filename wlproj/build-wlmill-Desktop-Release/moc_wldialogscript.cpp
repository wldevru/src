/****************************************************************************
** Meta object code from reading C++ file 'wldialogscript.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../wlmill/wldialogscript.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'wldialogscript.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WLDialog_t {
    QByteArrayData data[11];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WLDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WLDialog_t qt_meta_stringdata_WLDialog = {
    {
QT_MOC_LITERAL(0, 0, 8), // "WLDialog"
QT_MOC_LITERAL(1, 9, 8), // "enterNum"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 11), // "enterString"
QT_MOC_LITERAL(4, 31, 11), // "enterCancel"
QT_MOC_LITERAL(5, 43, 11), // "showMessage"
QT_MOC_LITERAL(6, 55, 3), // "txt"
QT_MOC_LITERAL(7, 59, 12), // "showEnterNum"
QT_MOC_LITERAL(8, 72, 15), // "showEnterString"
QT_MOC_LITERAL(9, 88, 12), // "showSaveFile"
QT_MOC_LITERAL(10, 101, 8) // "lastFile"

    },
    "WLDialog\0enterNum\0\0enterString\0"
    "enterCancel\0showMessage\0txt\0showEnterNum\0"
    "showEnterString\0showSaveFile\0lastFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WLDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    1,   52,    2, 0x06 /* Public */,
       4,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   56,    2, 0x0a /* Public */,
       7,    1,   59,    2, 0x0a /* Public */,
       8,    1,   62,    2, 0x0a /* Public */,
       9,    2,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    6,   10,

       0        // eod
};

void WLDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WLDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->enterNum((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 1: _t->enterString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->enterCancel(); break;
        case 3: _t->showMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->showEnterNum((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->showEnterString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->showSaveFile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WLDialog::*)(double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDialog::enterNum)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WLDialog::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDialog::enterString)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WLDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WLDialog::enterCancel)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WLDialog::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_WLDialog.data,
    qt_meta_data_WLDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WLDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WLDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WLDialog.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int WLDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void WLDialog::enterNum(double _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void WLDialog::enterString(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WLDialog::enterCancel()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
