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

include(../UtilsLib/import.pri)
include(../BaseLib/import.pri)

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

DISTFILES += AppPlugin.json

RESOURCES += \
    AppPlugin.qrc
