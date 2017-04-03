include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_plugin_services
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui
QT += qml

CONFIG += plugin

include(../cutehmi_base.pri)
include(../cutehmi_services.pri)

SOURCES += \
    src/services/plugin/Plugin.cpp \
    src/services/plugin/PluginNodeData.cpp

HEADERS += \
    src/services/plugin/Plugin.hpp \
    src/services/plugin/PluginNodeData.hpp

DISTFILES += PluginServices.json

RESOURCES += \
    PluginServices.qrc
