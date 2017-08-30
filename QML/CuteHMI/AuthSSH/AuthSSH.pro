include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_authssh_1_qml)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_authssh_1_qml_pl.ts

include(../../../UtilsLib/import.pri)
include(../../../BaseLib/import.pri)
include(../../../cutehmi_authssh_1_lib/import.pri)

HEADERS += \
    src/CuteHMIAuthSSHQMLPlugin.hpp

SOURCES += \
    src/CuteHMIAuthSSHQMLPlugin.cpp \

DISTFILES += \ 
    qmldir

RESOURCES +=
