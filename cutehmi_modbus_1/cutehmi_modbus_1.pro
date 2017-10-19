include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_modbus_1
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui
QT += qml

CONFIG += plugin

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_base_1_lib/import.pri)
include(../cutehmi_services_1_lib/import.pri)
include(../cutehmi_modbus_1_lib/import.pri)
include(../libmodbus.pri)

SOURCES += \
    src/modbus/plugin/ModbusNodeData.cpp \
    src/modbus/plugin/Plugin.cpp \
    src/modbus/plugin/PluginNodeData.cpp \
    src/modbus/plugin/macros.cpp

HEADERS += \
    src/modbus/plugin/ModbusNodeData.hpp \
    src/modbus/plugin/Plugin.hpp \
    src/modbus/plugin/PluginNodeData.hpp \
    src/modbus/plugin/macros.hpp

DISTFILES += cutehmi_modbus_1.json

RESOURCES += \
    cutehmi_modbus_1.qrc
