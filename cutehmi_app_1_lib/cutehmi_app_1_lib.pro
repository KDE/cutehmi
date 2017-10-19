include(../common.pri)
include(libdef.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget($$CUTEHMI_APP_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.
VERSION = $$CUTEHMI_APP_LIBVERSION

#<workaround ref="cutehmi_app_1_lib-1" target="Qt" cause="bug">
QT += widgets
#</workaround>

# Configure the library for building.
DEFINES += CUTEHMI_APP_BUILD
DEFINES += CUTEHMI_APP_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_APP_LIBNAME}_pl.ts

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_base_1_lib/import.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/app/internal/macros.cpp \
    src/app/CuteApp.cpp

HEADERS += \
    include/app/internal/common.hpp \
    include/app/internal/macros.hpp \
    include/app/internal/platform.hpp \
    include/app/CuteApp.hpp

DISTFILES += \
    import.pri \
    libdef.pri

RESOURCES +=

STATECHARTS +=
