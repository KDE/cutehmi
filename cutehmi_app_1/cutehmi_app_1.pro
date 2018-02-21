include(../common.pri)
include(libdef.pri)

TEMPLATE = lib

TARGET = $$cutehmiTarget($$CUTEHMI_APP_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.

VERSION = $$CUTEHMI_APP_LIBVERSION

CONFIG += plugin

# Configure the library for building.
DEFINES += CUTEHMI_APP_BUILD
DEFINES += CUTEHMI_APP_DYNAMIC

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_APP_LIBNAME}_pl.ts

QT -= gui
#<workaround ref="cutehmi_app_1-1" target="Qt" cause="bug">
QT += widgets
#</workaround>

include(../cutehmi_1/import.pri)

SOURCES += \
    src/app/plugin/Plugin.cpp \
    src/app/plugin/PluginNodeData.cpp \
    src/app/plugin/MainScreen.cpp \
    src/app/plugin/ScreensNodeData.cpp \
    src/app/CuteApp.cpp \
    src/app/logging.cpp

HEADERS += \
    src/app/plugin/Plugin.hpp \
    src/app/plugin/PluginNodeData.hpp \
    src/app/plugin/MainScreen.hpp \
    src/app/plugin/ScreensNodeData.hpp \
    include/app/internal/common.hpp \
    include/app/internal/platform.hpp \
    include/app/CuteApp.hpp \
    include/app/logging.hpp

DISTFILES += cutehmi_app_1.json \
    import.pri \
    libdef.pri \
    dev/cutehmi_app_1-1.workaround.Qt.bug.txt

RESOURCES += \
    cutehmi_app_1.qrc
