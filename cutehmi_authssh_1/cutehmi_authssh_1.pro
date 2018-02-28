include(../common.pri)
include(libdef.pri)

TEMPLATE = lib

DESTDIR = $$LIB_DESTDIR

TARGET = $$cutehmiTarget($$CUTEHMI_AUTHSSH_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.

VERSION = $$CUTEHMI_AUTHSSH_LIBVERSION

CONFIG += plugin

# Configure the library for building.
DEFINES += CUTEHMI_AUTHSSH_BUILD
DEFINES += CUTEHMI_AUTHSSH_DYNAMIC

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_AUTHSSH_LIBNAME}_pl.ts

QT -= gui
QT += network

include(../cutehmi_1/import.pri)
include(../cutehmi_xml_1/import.pri)
include(../libssh.pri)


SOURCES += \
    src/cutehmi/authssh/plugin/Plugin.cpp \
    src/cutehmi/authssh/plugin/PluginNodeData.cpp \
    src/cutehmi/authssh/plugin/AuthSSHNodeData.cpp \
    src/cutehmi/authssh/AbstractChannel.cpp \
    src/cutehmi/authssh/Client.cpp \
    src/cutehmi/authssh/ForwardChannel.cpp \
    src/cutehmi/authssh/Session.cpp \
    src/cutehmi/authssh/internal/ChannelsThread.cpp \
    src/cutehmi/authssh/internal/TunnelEntrance.cpp \
    src/cutehmi/authssh/logging.cpp

HEADERS += \
    src/cutehmi/authssh/plugin/Plugin.hpp \
    src/cutehmi/authssh/plugin/PluginNodeData.hpp \
    src/cutehmi/authssh/plugin/AuthSSHNodeData.hpp \
    include/cutehmi/authssh/AbstractChannel.hpp \
    include/cutehmi/authssh/Client.hpp \
    include/cutehmi/authssh/Exception.hpp \
    include/cutehmi/authssh/ForwardChannel.hpp \
    include/cutehmi/authssh/Session.hpp \
    include/cutehmi/authssh/internal/ChannelsThread.hpp \
    include/cutehmi/authssh/internal/common.hpp \
    include/cutehmi/authssh/internal/platform.hpp \
    include/cutehmi/authssh/internal/TunnelEntrance.hpp \
    include/cutehmi/authssh/logging.hpp

DISTFILES += cutehmi_authssh_1.json \
    import.pri \
    libdef.pri \
    dev/cutehmi_authssh_1-1.workaround.libssh.bug.txt \
    dev/cutehmi_authssh_1-2.workaround.libssh.bug.txt \
    dev/cutehmi_authssh_1-3.workaround.libssh.design.txt \
    dev/cutehmi_authssh_1-4.workaround.libssh.design.txt

RESOURCES += cutehmi_authssh_1.qrc
