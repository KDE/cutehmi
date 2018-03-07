include(../../common.pri)
include(libdef.pri)

TEMPLATE = lib

DESTDIR = $$MODULES_DESTDIR

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
include(../cutehmi_xml_1/import.pri)

SOURCES += \
    src/cutehmi/app/plugin/Plugin.cpp \
    src/cutehmi/app/plugin/PluginNodeData.cpp \
    src/cutehmi/app/plugin/ScreensNodeData.cpp \
    src/cutehmi/app/CuteApp.cpp \
    src/cutehmi/app/logging.cpp \
    src/cutehmi/app/MainScreen.cpp

HEADERS += \
    src/cutehmi/app/plugin/Plugin.hpp \
    src/cutehmi/app/plugin/PluginNodeData.hpp \
    src/cutehmi/app/plugin/ScreensNodeData.hpp \
    include/cutehmi/app/internal/common.hpp \
    include/cutehmi/app/internal/platform.hpp \
    include/cutehmi/app/CuteApp.hpp \
    include/cutehmi/app/logging.hpp \
    include/cutehmi/app/MainScreen.hpp

DISTFILES += cutehmi_app_1.json \
    import.pri \
    libdef.pri \
    dev/cutehmi_app_1-1.workaround.Qt.bug.txt

RESOURCES += \
    cutehmi_app_1.qrc
