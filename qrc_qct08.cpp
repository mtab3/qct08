/****************************************************************************
** Resource object code
**
** Created by: The Resource Compiler for Qt version 5.3.2
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtCore/qglobal.h>

static const unsigned char qt_resource_data[] = {
  // /usr/home/tabuchi/prog/qct08/qct08.key
  0x0,0x0,0x0,0x10,
  0x41,
  0x52,0x45,0x49,0x53,0x44,0x72,0x69,0x76,0x65,0x72,0x30,0x30,0x30,0x31,0xa,
  
};

static const unsigned char qt_resource_name[] = {
  // qct08.key
  0x0,0x9,
  0x7,0x3b,0xbe,0x89,
  0x0,0x71,
  0x0,0x63,0x0,0x74,0x0,0x30,0x0,0x38,0x0,0x2e,0x0,0x6b,0x0,0x65,0x0,0x79,
  
};

static const unsigned char qt_resource_struct[] = {
  // :
  0x0,0x0,0x0,0x0,0x0,0x2,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x1,
  // :/qct08.key
  0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x0,0x0,0x0,0x0,

};

QT_BEGIN_NAMESPACE

extern Q_CORE_EXPORT bool qRegisterResourceData
    (int, const unsigned char *, const unsigned char *, const unsigned char *);

extern Q_CORE_EXPORT bool qUnregisterResourceData
    (int, const unsigned char *, const unsigned char *, const unsigned char *);

QT_END_NAMESPACE


int QT_MANGLE_NAMESPACE(qInitResources_qct08)()
{
    QT_PREPEND_NAMESPACE(qRegisterResourceData)
        (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qct08))

int QT_MANGLE_NAMESPACE(qCleanupResources_qct08)()
{
    QT_PREPEND_NAMESPACE(qUnregisterResourceData)
       (0x01, qt_resource_struct, qt_resource_name, qt_resource_data);
    return 1;
}

Q_DESTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qCleanupResources_qct08))

