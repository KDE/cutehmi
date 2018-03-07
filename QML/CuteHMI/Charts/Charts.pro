include(../../../common.pri)

TEMPLATE = lib

DESTDIR = $$QML_DESTDIR/CuteHMI/Charts/plugins

TARGET = $$qtLibraryTarget(cutehmi_charts_1_qml)

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_charts_1_qml_pl.ts

include(../../../modules/cutehmi_1/import.pri)
include(../../../modules/cutehmi_charts_1/import.pri)

HEADERS += \
    src/CuteHMIChartsQMLPlugin.hpp \
    src/cutehmi/charts/qml/ScatterPlot.hpp \
    src/cutehmi/charts/qml/LinearAxis.hpp \
    src/cutehmi/charts/qml/ValueAxis.hpp \
    src/cutehmi/charts/qml/DateTimeAxis.hpp \
    src/cutehmi/charts/qml/PlotArea.hpp \
    src/cutehmi/charts/qml/CartesianAxis.hpp \
    src/cutehmi/charts/qml/TickedAxis.hpp

SOURCES += \
    src/CuteHMIChartsQMLPlugin.cpp \
    src/cutehmi/charts/qml/ScatterPlot.cpp \
    src/cutehmi/charts/qml/ValueAxis.cpp \
    src/cutehmi/charts/qml/DateTimeAxis.cpp \
    src/cutehmi/charts/qml/PlotArea.cpp \
    src/cutehmi/charts/qml/CartesianAxis.cpp \
    src/cutehmi/charts/qml/LinearAxis.cpp \
    src/cutehmi/charts/qml/TickedAxis.cpp

DISTFILES += \ 
    qmldir \
    plugins.qmltypes \
    Chart.qml

RESOURCES +=

QMAKE_POST_LINK += $$cutehmiCopyFiles($$DISTFILES, $$DESTDIR/..)
