include(../common.pri)

TARGET = cutehmi_plugin_modbus_test
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/tests

QT -= gui
QT += qml testlib

include(../cutehmi_base.pri)
include(../cutehmi_modbus.pri)
include(../libmodbus.pri)
#LIBS += -L$$PWD/../../../bin/plugins -l$$qtLibraryTarget(cutehmi_plugin_modbus)

HEADERS += \
    test/pluginModbus/PluginTest.hpp \
    src/pluginModbus/Plugin.hpp

SOURCES += \
    test/pluginModbus/PluginTest.cpp \
    src/pluginModbus/Plugin.cpp

DISTFILES +=
