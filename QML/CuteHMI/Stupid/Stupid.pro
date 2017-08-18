include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_stupid_1_qml)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_stupid_qml_1_pl.ts

include(../../../UtilsLib/import.pri)
include(../../../BaseLib/import.pri)
include(../../../ChartsLib/import.pri)
include(../../../StupidLib/import.pri)

HEADERS += \
    src/CuteHMIStupidQMLPlugin.hpp

SOURCES += \
    src/CuteHMIStupidQMLPlugin.cpp

DISTFILES += \ 
    qmldir \
    DS18B20Controller.qml \
    DS18B20Controller.js

RESOURCES +=
