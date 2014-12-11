/****************************************************************************
** Meta object code from reading C++ file 'Main.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Main.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Main.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Main_t {
    QByteArrayData data[13];
    char stringdata[95];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Main_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Main_t qt_meta_stringdata_Main = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 8),
QT_MOC_LITERAL(2, 14, 0),
QT_MOC_LITERAL(3, 15, 4),
QT_MOC_LITERAL(4, 20, 4),
QT_MOC_LITERAL(5, 25, 4),
QT_MOC_LITERAL(6, 30, 4),
QT_MOC_LITERAL(7, 35, 9),
QT_MOC_LITERAL(8, 45, 3),
QT_MOC_LITERAL(9, 49, 11),
QT_MOC_LITERAL(10, 61, 8),
QT_MOC_LITERAL(11, 70, 11),
QT_MOC_LITERAL(12, 82, 12)
    },
    "Main\0ParseAns\0\0SMsg\0smsg\0AMsg\0amsg\0"
    "AnsIsBusy\0msg\0AnsGetValue\0AnsReset\0"
    "AnsQGetData\0AnsQFinalize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Main[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x08 /* Private */,
       7,    1,   49,    2, 0x08 /* Private */,
       9,    1,   52,    2, 0x08 /* Private */,
      10,    1,   55,    2, 0x08 /* Private */,
      11,    1,   58,    2, 0x08 /* Private */,
      12,    1,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    8,

       0        // eod
};

void Main::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Main *_t = static_cast<Main *>(_o);
        switch (_id) {
        case 0: _t->ParseAns((*reinterpret_cast< SMsg(*)>(_a[1])),(*reinterpret_cast< AMsg(*)>(_a[2]))); break;
        case 1: _t->AnsIsBusy((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 2: _t->AnsGetValue((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 3: _t->AnsReset((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 4: _t->AnsQGetData((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 5: _t->AnsQFinalize((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Main::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Main.data,
      qt_meta_data_Main,  qt_static_metacall, 0, 0}
};


const QMetaObject *Main::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Main::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Main.stringdata))
        return static_cast<void*>(const_cast< Main*>(this));
    return QObject::qt_metacast(_clname);
}

int Main::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
