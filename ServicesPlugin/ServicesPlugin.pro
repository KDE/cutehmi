include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_services_1
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui
QT += qml

CONFIG += plugin

include(../UtilsLib/import.pri)
include(../BaseLib/import.pri)
include(../ServicesLib/import.pri)

SOURCES += \
    src/services/plugin/Plugin.cpp \
    src/services/plugin/PluginNodeData.cpp

HEADERS += \
    src/services/plugin/Plugin.hpp \
    src/services/plugin/PluginNodeData.hpp

DISTFILES += ServicesPlugin.json

RESOURCES += \
    ServicesPlugin.qrc
