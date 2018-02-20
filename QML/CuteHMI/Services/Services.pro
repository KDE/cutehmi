include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_services_1_qml)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_services_1_qml_pl.ts

include(../../../cutehmi_utils_1_lib/import.pri)
include(../../../cutehmi_1/import.pri)
include(../../../cutehmi_services_1_lib/import.pri)

DISTFILES += \
    qmldir \
    designer/Services.metainfo

RESOURCES +=

HEADERS += \
    src/CuteHMIServicesQMLPlugin.hpp

SOURCES += \
    src/CuteHMIServicesQMLPlugin.cpp

