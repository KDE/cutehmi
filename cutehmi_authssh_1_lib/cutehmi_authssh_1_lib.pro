include(../common.pri)
include(version.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_authssh_1)

QT -= gui
QT += qml concurrent

# Set version.
VER_MAJ = $$CUTEHMI_AUTHSSH_1_MAJOR
VER_MIN = $$CUTEHMI_AUTHSSH_1_MINOR
VER_PAT = $$CUTEHMI_AUTHSSH_1_MICRO

# Configure the library for building.
DEFINES += CUTEHMI_AUTHSSH_1_BUILD
DEFINES += CUTEHMI_AUTHSSH_1_DYNAMIC
#CONFIG += shared

# Translations.
# TRANSLATIONS = locale/cutehmi_authssh_1_pl.ts

include(../UtilsLib/import.pri)
include(../BaseLib/import.pri)
include(../ServicesLib/import.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/authssh_1/SocketListener.cpp \
    src/authssh_1/SSHClient.cpp

HEADERS += \
    include/authssh_1/SocketListener.hpp \
    include/authssh_1/SSHClient.hpp

DISTFILES += \
    import.pri \
    version.pri

RESOURCES +=

STATECHARTS +=
