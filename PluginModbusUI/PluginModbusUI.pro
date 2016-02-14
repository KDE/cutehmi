include(../common.pri)

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
include(../cutehmi_widgets.pri)
include(../cutehmi_modbus.pri)
include(../libmodbus.pri)

SOURCES += \
    src/pluginModbusUI/Plugin.cpp \
    src/pluginModbusUI/ClientControlWidget.cpp \
    src/pluginModbusUI/UIVisitorDelegate.cpp \
    src/pluginModbusUI/VisitorDelegate.cpp

HEADERS += \
    src/pluginModbusUI/Plugin.hpp \
    src/pluginModbusUI/ClientControlWidget.hpp \
    src/pluginModbusUI/UIVisitorDelegate.hpp \
    src/pluginModbusUI/VisitorDelegate.hpp

DISTFILES += PluginModbusUI.json

RESOURCES += \
    PluginModbusUI.qrc

FORMS += \
    src/pluginModbusUI/ClientControlWidget.ui \
    src/pluginModbusUI/_ClientControlWidget.ui
