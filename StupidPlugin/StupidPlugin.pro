include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_stupid_1
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui
QT += qml sql

CONFIG += plugin

include(../UtilsLib/import.pri)
include(../BaseLib/import.pri)
include(../ServicesLib/import.pri)
include(../ChartsLib/import.pri)
include(../StupidLib/import.pri)

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

DISTFILES += StupidPlugin.json

RESOURCES += \
    StupidPlugin.qrc
