include(../common.pri)
include(libdef.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget($$CUTEHMI_AUTHSSH_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.
VERSION = $$CUTEHMI_AUTHSSH_LIBVERSION

QT -= gui
QT += qml concurrent network

# Configure the library for building.
DEFINES += CUTEHMI_AUTHSSH_BUILD
DEFINES += CUTEHMI_AUTHSSH_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_AUTHSSH_LIBNAME}_pl.ts

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_base_1_lib/import.pri)
include(../cutehmi_services_1_lib/import.pri)
include(../libssh.pri)


unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/authssh/internal/macros.cpp \
    src/authssh/AbstractChannel.cpp \
    src/authssh/ForwardChannel.cpp \
    src/authssh/internal/ChannelsThread.cpp \
    src/authssh/internal/TunnelEntrance.cpp \
    src/authssh/Session.cpp \
    src/authssh/Client.cpp

HEADERS += \
    include/authssh/internal/common.hpp \
    include/authssh/internal/macros.hpp \
    include/authssh/internal/platform.hpp \
    include/authssh/Exception.hpp \
    include/authssh/AbstractChannel.hpp \
    include/authssh/ForwardChannel.hpp \
    include/authssh/internal/ChannelsThread.hpp \
    include/authssh/internal/TunnelEntrance.hpp \
    include/authssh/Session.hpp \
    include/authssh/Client.hpp

DISTFILES += \
    import.pri \
    libdef.pri

RESOURCES +=

STATECHARTS +=
