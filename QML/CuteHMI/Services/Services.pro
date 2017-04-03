include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_qmlplugin_services)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_qmlplugin_services_pl.ts

include(../../../cutehmi_base.pri)
include(../../../cutehmi_services.pri)

DISTFILES += \
    qmldir \
    designer/Services.metainfo

RESOURCES +=

HEADERS += \
    src/CuteHMIServicesQMLPlugin.hpp

SOURCES += \
    src/CuteHMIServicesQMLPlugin.cpp

