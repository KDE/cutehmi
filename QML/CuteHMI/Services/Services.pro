include(../../../common.pri)

TEMPLATE = lib

DESTDIR = $$QML_DESTDIR/CuteHMI/Services/plugins

TARGET = $$qtLibraryTarget(cutehmi_services_1_qml)

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_services_1_qml_pl.ts

include(../../../cutehmi_1/import.pri)
include(../../../cutehmi_services_1/import.pri)

DISTFILES += \
    qmldir \
    plugins.qmltypes \
    designer/Services.metainfo

RESOURCES +=

HEADERS += \
    src/CuteHMIServicesQMLPlugin.hpp

SOURCES += \
    src/CuteHMIServicesQMLPlugin.cpp

QMAKE_POST_LINK += $$cutehmiCopyFiles($$DISTFILES, $$DESTDIR/..)
