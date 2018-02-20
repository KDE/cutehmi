include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_authssh_1
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui
QT += network

CONFIG += plugin

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_1/import.pri)
include(../cutehmi_authssh_1_lib/import.pri)
include(../libssh.pri)


SOURCES += \
    src/authssh/plugin/Plugin.cpp \
    src/authssh/plugin/PluginNodeData.cpp \
    src/authssh/plugin/AuthSSHNodeData.cpp \
    src/authssh/AbstractChannel.cpp \
    src/authssh/Client.cpp \
    src/authssh/ForwardChannel.cpp \
    src/authssh/Session.cpp \
    src/authssh/internal/ChannelsThread.cpp \
    src/authssh/internal/TunnelEntrance.cpp \
    src/authssh/macros.cpp

HEADERS += \
    src/authssh/plugin/macros.hpp \
    src/authssh/plugin/Plugin.hpp \
    src/authssh/plugin/PluginNodeData.hpp \
    src/authssh/plugin/AuthSSHNodeData.hpp \
    include/authssh/AbstractChannel.hpp \
    include/authssh/Client.hpp \
    include/authssh/Exception.hpp \
    include/authssh/ForwardChannel.hpp \
    include/authssh/Session.hpp \
    include/authssh/internal/ChannelsThread.hpp \
    include/authssh/internal/common.hpp \
    include/authssh/internal/platform.hpp \
    include/authssh/internal/TunnelEntrance.hpp \
    include/authssh/macros.hpp

DISTFILES += cutehmi_authssh_1.json \
    import.pri \
    libdef.pri \
    dev/cutehmi_authssh_1-1.workaround.libssh.bug.txt \
    dev/cutehmi_authssh_1-2.workaround.libssh.bug.txt \
    dev/cutehmi_authssh_1-3.workaround.libssh.design.txt \
    dev/cutehmi_authssh_1-4.workaround.libssh.design.txt

RESOURCES += cutehmi_authssh_1.qrc
