include(../../../common.pri)

TEMPLATE = lib

DESTDIR = $$QML_DESTDIR/CuteHMI/AuthSSH/plugins

TARGET = $$qtLibraryTarget(cutehmi_authssh_1_qml)

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_authssh_1_qml_pl.ts

include(../../../cutehmi_1/import.pri)
include(../../../cutehmi_authssh_1/import.pri)
include(../../../libssh.pri)


HEADERS += \
    src/CuteHMIAuthSSHQMLPlugin.hpp

SOURCES += \
    src/CuteHMIAuthSSHQMLPlugin.cpp \

DISTFILES += \ 
    qmldir \
    plugins.qmltypes

RESOURCES +=

QMAKE_POST_LINK += $$cutehmiCopyFiles($$DISTFILES, $$DESTDIR/..)
