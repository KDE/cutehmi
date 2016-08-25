include(../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_stupid)

QT -= gui
QT += qml concurrent sql

# Configure the library for building
VER_MAJ = $$CUTEHMI_STUPID_MAJOR
VER_MIN = 0
VER_PAT = 0
DEFINES += CUTEHMI_STUPID_BUILD
DEFINES += CUTEHMI_STUPID_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/cutehmi_stupid_pl.ts

include(../cutehmi_base.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/stupid/Client.cpp

HEADERS += \
    src/platform.hpp \
    src/stupid/Client.hpp

DISTFILES +=

RESOURCES +=
