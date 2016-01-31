include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_plugin_modbus
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui
QT += qml

CONFIG += plugin

include(../cutehmi_base.pri)
include(../cutehmi_modbus.pri)
include(../libmodbus.pri)

SOURCES += \
    src/pluginModbus/Plugin.cpp

HEADERS += \
    src/pluginModbus/Plugin.hpp

DISTFILES += PluginModbus.json

RESOURCES += \
    PluginModbus.qrc
