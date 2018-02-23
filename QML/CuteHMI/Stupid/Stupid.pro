include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_stupid_1_qml)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_stupid_qml_1_pl.ts

include(../../../cutehmi_1/import.pri)
include(../../../cutehmi_charts_1/import.pri)
include(../../../cutehmi_stupid_1/import.pri)

HEADERS += \
    src/CuteHMIStupidQMLPlugin.hpp

SOURCES += \
    src/CuteHMIStupidQMLPlugin.cpp

DISTFILES += \ 
    qmldir \
    DS18B20Controller.qml \
    DS18B20Controller.js

RESOURCES +=
