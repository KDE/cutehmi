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
    src/charts/ScatterPlot.hpp \
    src/charts/LinearAxis.hpp \
    src/charts/ValueAxis.hpp \
    src/charts/DateTimeAxis.hpp \
    src/charts/PlotArea.hpp \
    src/charts/LabeledAxisTrait.hpp \
    src/charts/LabeledAxis.hpp \
    src/charts/CartesianAxis.hpp

SOURCES += \
    src/CuteHMIChartsQMLPlugin.cpp \
    src/charts/ScatterPlot.cpp \
    src/charts/LinearAxis.cpp \
    src/charts/ValueAxis.cpp \
    src/charts/DateTimeAxis.cpp \
    src/charts/PlotArea.cpp \
    src/charts/LabeledAxis.cpp \
    src/charts/CartesianAxis.cpp

DISTFILES += \ 
    qmldir \
    Chart.qml

RESOURCES +=
