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

include(../UtilsLib/import.pri)
include(../BaseLib/import.pri)

SOURCES += \
    src/authssh/plugin/macros.cpp \
    src/authssh/plugin/Plugin.cpp

HEADERS += \
    src/authssh/plugin/macros.hpp \
    src/authssh/plugin/Plugin.hpp

DISTFILES += cutehmi_authssh_1.json

RESOURCES += cutehmi_authssh_1.qrc
