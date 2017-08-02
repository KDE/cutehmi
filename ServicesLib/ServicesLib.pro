include(../common.pri)
include(version.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_services)

QT -= gui
QT += qml

# Set version.
VER_MAJ = $$CUTEHMI_SERVICES_MAJOR
VER_MIN = $$CUTEHMI_SERVICES_MINOR
VER_PAT = $$CUTEHMI_SERVICES_MICRO

# Configure the library for building.
DEFINES += CUTEHMI_SERVICES_BUILD
DEFINES += CUTEHMI_SERVICES_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/cutehmi_services_pl.ts

include(../UtilsLib/import.pri)
include(../BaseLib/import.pri)

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
    version.pri

RESOURCES +=
