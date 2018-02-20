include(../common.pri)
include(libdef.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget($$CUTEHMI_SERVICES_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.
VERSION = $$CUTEHMI_SERVICES_LIBVERSION

QT -= gui
QT += qml

# Configure the library for building.
DEFINES += CUTEHMI_SERVICES_BUILD
DEFINES += CUTEHMI_SERVICES_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_SERVICES_LIBNAME}_pl.ts

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_1/import.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/services/Service.cpp \
    src/services/ServiceRegistry.cpp \
    src/services/internal/macros.cpp

HEADERS += \
    include/services/Service.hpp \
    include/services/ServiceRegistry.hpp \
    include/services/internal/platform.hpp \
    include/services/internal/common.hpp \
    include/services/internal/macros.hpp

DISTFILES += \
    import.pri \
    libdef.pri

RESOURCES +=
