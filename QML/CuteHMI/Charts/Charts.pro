include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_qmlplugin_charts)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_qmlplugin_charts_pl.ts

include(../../../cutehmi_charts.pri)

HEADERS += \
    src/CuteHMIChartsQMLPlugin.hpp \
    src/charts/ScatterPlot.hpp

SOURCES += \
    src/CuteHMIChartsQMLPlugin.cpp \
    src/charts/ScatterPlot.cpp

DISTFILES += \ 
    qmldir

RESOURCES +=
