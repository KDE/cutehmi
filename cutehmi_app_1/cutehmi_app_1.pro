include(../common.pri)
include(libdef.pri)

TEMPLATE = lib
TARGET = $$cutehmiTarget(cutehmi_app_1)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.

VERSION = $$CUTEHMI_APP_LIBVERSION

CONFIG += plugin

QT -= gui
#<workaround ref="cutehmi_app_1_lib-1" target="Qt" cause="bug">
QT += widgets
#</workaround>

# Configure the library for building.
DEFINES += CUTEHMI_APP_BUILD
DEFINES += CUTEHMI_APP_DYNAMIC

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_1/import.pri)

SOURCES += \
    src/app/plugin/Plugin.cpp \
    src/app/plugin/PluginNodeData.cpp \
    src/app/plugin/macros.cpp \
    src/app/plugin/MainScreen.cpp \
    src/app/plugin/ScreensNodeData.cpp \
    src/app/CuteApp.cpp \
    src/app/internal/macros.cpp

HEADERS += \
    src/app/plugin/Plugin.hpp \
    src/app/plugin/PluginNodeData.hpp \
    src/app/plugin/macros.hpp \
    src/app/plugin/MainScreen.hpp \
    src/app/plugin/ScreensNodeData.hpp \
    include/app/internal/common.hpp \
    include/app/internal/macros.hpp \
    include/app/internal/platform.hpp \
    include/app/CuteApp.hpp

DISTFILES += cutehmi_app_1.json \
    import.pri \
    libdef.pri

RESOURCES += \
    cutehmi_app_1.qrc
