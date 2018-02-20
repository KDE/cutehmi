include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_authssh_1_qml)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_authssh_1_qml_pl.ts

include(../../../cutehmi_utils_1_lib/import.pri)
include(../../../cutehmi_1/import.pri)
include(../../../cutehmi_authssh_1_lib/import.pri)
include(../../../libssh.pri)


HEADERS += \
    src/CuteHMIAuthSSHQMLPlugin.hpp

SOURCES += \
    src/CuteHMIAuthSSHQMLPlugin.cpp \

DISTFILES += \ 
    qmldir

RESOURCES +=
