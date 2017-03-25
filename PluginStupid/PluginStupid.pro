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
include(../cutehmi_services.pri)
include(../cutehmi_charts.pri)
include(../cutehmi_stupid.pri)

SOURCES += \
    src/stupid/plugin/Plugin.cpp \
    src/stupid/plugin/StupidNodeData.cpp \
    src/stupid/plugin/PluginNodeData.cpp \
    src/stupid/plugin/macros.cpp

HEADERS += \
    src/stupid/plugin/Plugin.hpp \
    src/stupid/plugin/StupidNodeData.hpp \
    src/stupid/plugin/PluginNodeData.hpp \
    src/stupid/plugin/macros.hpp

DISTFILES += PluginStupid.json

RESOURCES += \
    PluginStupid.qrc
