include(../../../common.pri)

TEMPLATE = lib

DESTDIR = $$QML_DESTDIR/CuteHMI/App/plugins

TARGET = $$qtLibraryTarget(cutehmi_app_1_qml)

QT += qml quick
#<workaround ref="cutehmi_app_1-1" target="Qt" cause="bug">
QT += widgets
#</workaround>

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_app_1_qml_pl.ts

include(../../../modules/cutehmi_1/import.pri)
include(../../../modules/cutehmi_app_1/import.pri)

DISTFILES += \
    qmldir \
    plugins.qmltypes \
    designer/App.metainfo

RESOURCES +=

HEADERS += \
    src/CuteHMIAppQMLPlugin.hpp

SOURCES += \
    src/CuteHMIAppQMLPlugin.cpp

QMAKE_POST_LINK += $$cutehmiCopyFiles($$DISTFILES, $$DESTDIR/..)
