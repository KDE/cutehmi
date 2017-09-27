include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_screenlock_1
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui

CONFIG += plugin

include(../UtilsLib/import.pri)
include(../BaseLib/import.pri)

SOURCES += \
    src/screenlock/plugin/macros.cpp \
    src/screenlock/plugin/Plugin.cpp \
    src/screenlock/plugin/PluginNodeData.cpp

HEADERS += \
    src/screenlock/plugin/macros.hpp \
    src/screenlock/plugin/Plugin.hpp \
    src/screenlock/plugin/PluginNodeData.hpp

DISTFILES += cutehmi_screenlock_1.json

RESOURCES += cutehmi_screenlock_1.qrc
