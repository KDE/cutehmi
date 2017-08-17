/****************************************************************************
** Meta object code from reading C++ file 'Plugin.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/authssh/plugin/Plugin.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Plugin.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_cutehmi__authssh__plugin__Plugin_t {
    QByteArrayData data[1];
    char stringdata0[33];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cutehmi__authssh__plugin__Plugin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cutehmi__authssh__plugin__Plugin_t qt_meta_stringdata_cutehmi__authssh__plugin__Plugin = {
    {
QT_MOC_LITERAL(0, 0, 32) // "cutehmi::authssh::plugin::Plugin"

    },
    "cutehmi::authssh::plugin::Plugin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cutehmi__authssh__plugin__Plugin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void cutehmi::authssh::plugin::Plugin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject cutehmi::authssh::plugin::Plugin::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_cutehmi__authssh__plugin__Plugin.data,
      qt_meta_data_cutehmi__authssh__plugin__Plugin,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *cutehmi::authssh::plugin::Plugin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cutehmi::authssh::plugin::Plugin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_cutehmi__authssh__plugin__Plugin.stringdata0))
        return static_cast<void*>(const_cast< Plugin*>(this));
    if (!strcmp(_clname, "base::IPlugin"))
        return static_cast< base::IPlugin*>(const_cast< Plugin*>(this));
    if (!strcmp(_clname, "base::IXMLBackendPlugin"))
        return static_cast< base::IXMLBackendPlugin*>(const_cast< Plugin*>(this));
    if (!strcmp(_clname, "cutehmi::base::IPlugin"))
        return static_cast< cutehmi::base::IPlugin*>(const_cast< Plugin*>(this));
    return QObject::qt_metacast(_clname);
}

int cutehmi::authssh::plugin::Plugin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}

QT_PLUGIN_METADATA_SECTION const uint qt_section_alignment_dummy = 42;

#ifdef QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xf8, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xe4, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'c',  'u',  't',  'e',  'h',  'm', 
    'i',  ':',  ':',  'b',  'a',  's',  'e',  ':', 
    ':',  'I',  'P',  'l',  'u',  'g',  'i',  'n', 
    0x1b, 0x08, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x06, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    ':',  ' ',  0xa1, 0x00, 0x07, 0x00, 'v',  'e', 
    'r',  's',  'i',  'o',  'n',  0x00, 0x00, 0x00,
    0x11, 0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, 0x95, 0x0e, 0x00, 0x00,
    0x08, 0x00, 'M',  'e',  't',  'a',  'D',  'a', 
    't',  'a',  0x00, 0x00, 'p',  0x00, 0x00, 0x00,
    0x09, 0x00, 0x00, 0x00, '`',  0x00, 0x00, 0x00,
    0x9b, 0x02, 0x00, 0x00, 0x02, 0x00, 'i',  'd', 
    0x11, 0x00, 'c',  'u',  't',  'e',  'h',  'm', 
    'i',  '_',  'a',  'u',  't',  'h',  's',  's', 
    'h',  '_',  '1',  0x00, 0x1a, 0x00, 0x00, 0x00,
    0x05, 0x00, 'm',  'i',  'n',  'o',  'r',  0x00,
    0x1a, 0x00, 0x00, 0x00, 0x05, 0x00, 'm',  'i', 
    'c',  'r',  'o',  0x00, 0x9b, 0x09, 0x00, 0x00,
    0x04, 0x00, 'n',  'a',  'm',  'e',  0x00, 0x00,
    0x12, 0x00, 'S',  'S',  'H',  ' ',  'A',  'u', 
    't',  'h',  'e',  'n',  't',  'i',  'c',  'a', 
    't',  'i',  'o',  'n',  0x0c, 0x00, 0x00, 0x00,
    '4',  0x00, 0x00, 0x00, '(',  0x00, 0x00, 0x00,
    '@',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    'd',  0x00, 0x00, 0x00, '0',  0x00, 0x00, 0x00,
    'X',  0x00, 0x00, 0x00, 'H',  0x00, 0x00, 0x00
};

#else // QT_NO_DEBUG

QT_PLUGIN_METADATA_SECTION
static const unsigned char qt_pluginMetaData[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', ' ',
    'q',  'b',  'j',  's',  0x01, 0x00, 0x00, 0x00,
    0xf8, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x00, 0x00,
    0xe4, 0x00, 0x00, 0x00, 0x1b, 0x03, 0x00, 0x00,
    0x03, 0x00, 'I',  'I',  'D',  0x00, 0x00, 0x00,
    0x16, 0x00, 'c',  'u',  't',  'e',  'h',  'm', 
    'i',  ':',  ':',  'b',  'a',  's',  'e',  ':', 
    ':',  'I',  'P',  'l',  'u',  'g',  'i',  'n', 
    0x15, 0x08, 0x00, 0x00, 0x08, 0x00, 'M',  'e', 
    't',  'a',  'D',  'a',  't',  'a',  0x00, 0x00,
    'p',  0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00,
    '`',  0x00, 0x00, 0x00, 0x9b, 0x02, 0x00, 0x00,
    0x02, 0x00, 'i',  'd',  0x11, 0x00, 'c',  'u', 
    't',  'e',  'h',  'm',  'i',  '_',  'a',  'u', 
    't',  'h',  's',  's',  'h',  '_',  '1',  0x00,
    0x1a, 0x00, 0x00, 0x00, 0x05, 0x00, 'm',  'i', 
    'n',  'o',  'r',  0x00, 0x1a, 0x00, 0x00, 0x00,
    0x05, 0x00, 'm',  'i',  'c',  'r',  'o',  0x00,
    0x9b, 0x09, 0x00, 0x00, 0x04, 0x00, 'n',  'a', 
    'm',  'e',  0x00, 0x00, 0x12, 0x00, 'S',  'S', 
    'H',  ' ',  'A',  'u',  't',  'h',  'e',  'n', 
    't',  'i',  'c',  'a',  't',  'i',  'o',  'n', 
    0x0c, 0x00, 0x00, 0x00, '4',  0x00, 0x00, 0x00,
    '(',  0x00, 0x00, 0x00, '@',  0x00, 0x00, 0x00,
    0x1b, 0x18, 0x00, 0x00, 0x09, 0x00, 'c',  'l', 
    'a',  's',  's',  'N',  'a',  'm',  'e',  0x00,
    0x06, 0x00, 'P',  'l',  'u',  'g',  'i',  'n', 
    '1',  0x00, 0x00, 0x00, 0x05, 0x00, 'd',  'e', 
    'b',  'u',  'g',  0x00, ':',  ' ',  0xa1, 0x00,
    0x07, 0x00, 'v',  'e',  'r',  's',  'i',  'o', 
    'n',  0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00,
    '0',  0x00, 0x00, 0x00, 0xb0, 0x00, 0x00, 0x00,
    0xc8, 0x00, 0x00, 0x00, 0xd4, 0x00, 0x00, 0x00
};
#endif // QT_NO_DEBUG

using namespace cutehmi;
using namespace cutehmi::authssh;
using namespace cutehmi::authssh::plugin;
QT_MOC_EXPORT_PLUGIN(cutehmi::authssh::plugin::Plugin, Plugin)

QT_WARNING_POP
QT_END_MOC_NAMESPACE
