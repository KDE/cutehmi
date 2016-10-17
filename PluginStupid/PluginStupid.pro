include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_plugin_stupid
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui
QT += qml sql

CONFIG += plugin

include(../cutehmi_base.pri)
include(../cutehmi_charts.pri)
include(../cutehmi_stupid.pri)

SOURCES += \
    src/pluginStupid/Plugin.cpp

HEADERS += \
    src/pluginStupid/Plugin.hpp

DISTFILES += PluginStupid.json

RESOURCES += \
    PluginStupid.qrc
