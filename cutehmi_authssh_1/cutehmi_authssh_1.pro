include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_authssh_1
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui

CONFIG += plugin

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_base_1_lib/import.pri)
include(../cutehmi_authssh_1_lib/import.pri)
include(../libssh.pri)


SOURCES += \
    src/authssh/plugin/macros.cpp \
    src/authssh/plugin/Plugin.cpp \
    src/authssh/plugin/PluginNodeData.cpp \
    src/authssh/plugin/AuthSSHNodeData.cpp

HEADERS += \
    src/authssh/plugin/macros.hpp \
    src/authssh/plugin/Plugin.hpp \
    src/authssh/plugin/PluginNodeData.hpp \
    src/authssh/plugin/AuthSSHNodeData.hpp

DISTFILES += cutehmi_authssh_1.json

RESOURCES += cutehmi_authssh_1.qrc
