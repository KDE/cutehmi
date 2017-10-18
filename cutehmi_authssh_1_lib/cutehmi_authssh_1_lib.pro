include(../common.pri)
include(libdef.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget($$CUTEHMI_AUTHSSH_LIBNAME)

QT -= gui
QT += qml concurrent

# Configure the library for building.
DEFINES += CUTEHMI_AUTHSSH_BUILD
DEFINES += CUTEHMI_AUTHSSH_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_AUTHSSH_LIBNAME}_pl.ts

include(../UtilsLib/import.pri)
include(../BaseLib/import.pri)
include(../ServicesLib/import.pri)
include(../libssh.pri)


unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/authssh/SocketListener.cpp \
    src/authssh/Auth.cpp \
    src/authssh/internal/macros.cpp \
    src/authssh/Client.cpp

HEADERS += \
    include/authssh/SocketListener.hpp \
    include/authssh/internal/common.hpp \
    include/authssh/internal/macros.hpp \
    include/authssh/internal/platform.hpp \
    include/authssh/Auth.hpp \
    include/authssh/Client.hpp \
    include/authssh/Exception.hpp

DISTFILES += \
    import.pri \
    libdef.pri

RESOURCES +=

STATECHARTS +=
