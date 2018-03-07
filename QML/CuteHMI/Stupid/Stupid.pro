include(../../../common.pri)

TEMPLATE = lib

DESTDIR = $$QML_DESTDIR/CuteHMI/Stupid/plugins

TARGET = $$qtLibraryTarget(cutehmi_stupid_1_qml)

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_stupid_qml_1_pl.ts

include(../../../modules/cutehmi_1/import.pri)
include(../../../modules/cutehmi_charts_1/import.pri)
include(../../../modules/cutehmi_stupid_1/import.pri)

HEADERS += \
    src/CuteHMIStupidQMLPlugin.hpp

SOURCES += \
    src/CuteHMIStupidQMLPlugin.cpp

DISTFILES += \ 
    qmldir \
    plugins.qmltypes \
    DS18B20Controller.qml \
    DS18B20Controller.js

RESOURCES +=

QMAKE_POST_LINK += $$cutehmiCopyFiles($$DISTFILES, $$DESTDIR/..)
