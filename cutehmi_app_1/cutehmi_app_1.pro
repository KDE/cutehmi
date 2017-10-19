include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_app_1
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui

CONFIG += plugin

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_base_1_lib/import.pri)

SOURCES += \
    src/app/plugin/Plugin.cpp \
    src/app/plugin/PluginNodeData.cpp \
    src/app/plugin/macros.cpp \
    src/app/plugin/MainScreen.cpp \
    src/app/plugin/ScreensNodeData.cpp

HEADERS += \
    src/app/plugin/Plugin.hpp \
    src/app/plugin/PluginNodeData.hpp \
    src/app/plugin/macros.hpp \
    src/app/plugin/MainScreen.hpp \
    src/app/plugin/ScreensNodeData.hpp

DISTFILES += cutehmi_app_1.json

RESOURCES += \
    cutehmi_app_1.qrc
