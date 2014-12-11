/****************************************************************************
** Meta object code from reading C++ file 'Body.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Body.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Body.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Body_t {
    QByteArrayData data[14];
    char stringdata[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Body_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Body_t qt_meta_stringdata_Body = {
    {
QT_MOC_LITERAL(0, 0, 4),
QT_MOC_LITERAL(1, 5, 8),
QT_MOC_LITERAL(2, 14, 0),
QT_MOC_LITERAL(3, 15, 4),
QT_MOC_LITERAL(4, 20, 4),
QT_MOC_LITERAL(5, 25, 5),
QT_MOC_LITERAL(6, 31, 4),
QT_MOC_LITERAL(7, 36, 9),
QT_MOC_LITERAL(8, 46, 3),
QT_MOC_LITERAL(9, 50, 11),
QT_MOC_LITERAL(10, 62, 8),
QT_MOC_LITERAL(11, 71, 14),
QT_MOC_LITERAL(12, 86, 11),
QT_MOC_LITERAL(13, 98, 12)
    },
    "Body\0ParseAns\0\0SMsg\0smsg\0CTMsg\0amsg\0"
    "AnsIsBusy\0msg\0AnsGetValue\0AnsReset\0"
    "AnsQInitialize\0AnsQGetData\0AnsQFinalize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Body[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x08 /* Private */,
       7,    1,   54,    2, 0x08 /* Private */,
       9,    1,   57,    2, 0x08 /* Private */,
      10,    1,   60,    2, 0x08 /* Private */,
      11,    1,   63,    2, 0x08 /* Private */,
      12,    1,   66,    2, 0x08 /* Private */,
      13,    1,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    8,

       0        // eod
};

void Body::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Body *_t = static_cast<Body *>(_o);
        switch (_id) {
        case 0: _t->ParseAns((*reinterpret_cast< SMsg(*)>(_a[1])),(*reinterpret_cast< CTMsg(*)>(_a[2]))); break;
        case 1: _t->AnsIsBusy((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 2: _t->AnsGetValue((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 3: _t->AnsReset((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 4: _t->AnsQInitialize((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 5: _t->AnsQGetData((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 6: _t->AnsQFinalize((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Body::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Body.data,
      qt_meta_data_Body,  qt_static_metacall, 0, 0}
};


const QMetaObject *Body::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Body::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Body.stringdata))
        return static_cast<void*>(const_cast< Body*>(this));
    return QObject::qt_metacast(_clname);
}

int Body::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
