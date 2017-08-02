include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_services_qml)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_services_qml_pl.ts

include(../../../UtilsLib/import.pri)
include(../../../BaseLib/import.pri)
include(../../../ServicesLib/import.pri)

DISTFILES += \
    qmldir \
    designer/Services.metainfo

RESOURCES +=

HEADERS += \
    src/CuteHMIServicesQMLPlugin.hpp

SOURCES += \
    src/CuteHMIServicesQMLPlugin.cpp

