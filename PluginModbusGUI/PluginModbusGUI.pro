include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_plugin_modbus_gui
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT += qml widgets

CONFIG += plugin

include(../cutehmi_base.pri)
include(../cutehmi_modbus.pri)
include(../libmodbus.pri)

SOURCES += \
    src/pluginModbusGUI/Plugin.cpp \
    src/pluginModbusGUI/ClientControlWidget.cpp \
    src/pluginModbusGUI/GUIVisitorDelegate.cpp

HEADERS += \
    src/pluginModbusGUI/Plugin.hpp \
    src/pluginModbusGUI/ClientControlWidget.hpp \
    src/pluginModbusGUI/GUIVisitorDelegate.hpp

DISTFILES += PluginModbusGUI.json

RESOURCES += \
    PluginModbusGUI.qrc

FORMS += \
    src/pluginModbusGUI/ClientControlWidget.ui \
    src/pluginModbusGUI/_ClientControlWidget.ui
