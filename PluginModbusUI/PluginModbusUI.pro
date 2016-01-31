include (../common.pri)

TEMPLATE = lib
TARGET = cutehmi_plugin_modbus_ui
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT += qml widgets

CONFIG += plugin

include(../cutehmi_base.pri)
include(../cutehmi_modbus.pri)

SOURCES += \
    src/modbus/ui/ClientControlWidget.cpp

HEADERS += \
    src/modbus/ui/ClientControlWidget.hpp

DISTFILES += PluginModbusUI.json

FORMS += \
    src/modbus/ui/ClientControlWidget.ui
