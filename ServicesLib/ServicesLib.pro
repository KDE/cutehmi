include(../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_services)

QT -= gui
QT += qml

# Configure the library for building
VER_MAJ = $$CUTEHMI_SERVICES_MAJOR
VER_MIN = 0
VER_PAT = 0
DEFINES += CUTEHMI_SERVICES_BUILD
DEFINES += CUTEHMI_SERVICES_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/cutehmi_services_pl.ts

include(../cutehmi_base.pri)

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

DISTFILES +=

RESOURCES +=
