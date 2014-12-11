/****************************************************************************
** Meta object code from reading C++ file 'Stars.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Stars.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Stars.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Stars_t {
    QByteArrayData data[19];
    char stringdata[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Stars_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Stars_t qt_meta_stringdata_Stars = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 17),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 6),
QT_MOC_LITERAL(4, 32, 1),
QT_MOC_LITERAL(5, 34, 11),
QT_MOC_LITERAL(6, 46, 9),
QT_MOC_LITERAL(7, 56, 4),
QT_MOC_LITERAL(8, 61, 3),
QT_MOC_LITERAL(9, 65, 11),
QT_MOC_LITERAL(10, 77, 8),
QT_MOC_LITERAL(11, 86, 14),
QT_MOC_LITERAL(12, 101, 11),
QT_MOC_LITERAL(13, 113, 12),
QT_MOC_LITERAL(14, 126, 15),
QT_MOC_LITERAL(15, 142, 4),
QT_MOC_LITERAL(16, 147, 12),
QT_MOC_LITERAL(17, 160, 23),
QT_MOC_LITERAL(18, 184, 9)
    },
    "Stars\0ConnectionIsReady\0\0Stars*\0s\0"
    "ReConnected\0AskIsBusy\0SMsg\0msg\0"
    "AskGetValue\0AskReset\0AskQInitialize\0"
    "AskQGetData\0AskQFinalize\0SetNewSVAddress\0"
    "item\0SetNewSVPort\0ReceiveMessageFromStars\0"
    "ReConnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Stars[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       5,    0,   77,    2, 0x06 /* Public */,
       6,    1,   78,    2, 0x06 /* Public */,
       9,    1,   81,    2, 0x06 /* Public */,
      10,    1,   84,    2, 0x06 /* Public */,
      11,    1,   87,    2, 0x06 /* Public */,
      12,    1,   90,    2, 0x06 /* Public */,
      13,    1,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,   96,    2, 0x0a /* Public */,
      16,    1,   99,    2, 0x0a /* Public */,
      17,    0,  102,    2, 0x0a /* Public */,
      18,    0,  103,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Stars::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Stars *_t = static_cast<Stars *>(_o);
        switch (_id) {
        case 0: _t->ConnectionIsReady((*reinterpret_cast< Stars*(*)>(_a[1]))); break;
        case 1: _t->ReConnected(); break;
        case 2: _t->AskIsBusy((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 3: _t->AskGetValue((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 4: _t->AskReset((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 5: _t->AskQInitialize((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 6: _t->AskQGetData((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 7: _t->AskQFinalize((*reinterpret_cast< SMsg(*)>(_a[1]))); break;
        case 8: _t->SetNewSVAddress((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->SetNewSVPort((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->ReceiveMessageFromStars(); break;
        case 11: _t->ReConnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Stars* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Stars::*_t)(Stars * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Stars::ConnectionIsReady)) {
                *result = 0;
            }
        }
        {
            typedef void (Stars::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Stars::ReConnected)) {
                *result = 1;
            }
        }
        {
            typedef void (Stars::*_t)(SMsg );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Stars::AskIsBusy)) {
                *result = 2;
            }
        }
        {
            typedef void (Stars::*_t)(SMsg );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Stars::AskGetValue)) {
                *result = 3;
            }
        }
        {
            typedef void (Stars::*_t)(SMsg );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Stars::AskReset)) {
                *result = 4;
            }
        }
        {
            typedef void (Stars::*_t)(SMsg );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Stars::AskQInitialize)) {
                *result = 5;
            }
        }
        {
            typedef void (Stars::*_t)(SMsg );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Stars::AskQGetData)) {
                *result = 6;
            }
        }
        {
            typedef void (Stars::*_t)(SMsg );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Stars::AskQFinalize)) {
                *result = 7;
            }
        }
    }
}

const QMetaObject Stars::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Stars.data,
      qt_meta_data_Stars,  qt_static_metacall, 0, 0}
};


const QMetaObject *Stars::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Stars::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Stars.stringdata))
        return static_cast<void*>(const_cast< Stars*>(this));
    return QObject::qt_metacast(_clname);
}

int Stars::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Stars::ConnectionIsReady(Stars * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Stars::ReConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void Stars::AskIsBusy(SMsg _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Stars::AskGetValue(SMsg _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Stars::AskReset(SMsg _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void Stars::AskQInitialize(SMsg _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void Stars::AskQGetData(SMsg _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void Stars::AskQFinalize(SMsg _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
