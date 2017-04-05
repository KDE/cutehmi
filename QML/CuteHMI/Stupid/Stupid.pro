include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_qmlplugin_stupid)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_qmlplugin_stupid_pl.ts

include(../../../cutehmi_base.pri)
include(../../../cutehmi_charts.pri)
include(../../../cutehmi_stupid.pri)

HEADERS += \
    src/CuteHMIStupidQMLPlugin.hpp

SOURCES += \
    src/CuteHMIStupidQMLPlugin.cpp

DISTFILES += \ 
    qmldir \
    DS18B20Controller.qml \
    DS18B20Controller.js

RESOURCES +=
