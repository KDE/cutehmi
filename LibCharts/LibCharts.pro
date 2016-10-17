include(../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_charts)

QT += qml quick

# Configure the library for building.
VER_MAJ = $$CUTEHMI_CHARTS_MAJOR
VER_MIN = 0
VER_PAT = 0
DEFINES += CUTEHMI_CHARTS_BUILD
DEFINES += CUTEHMI_CHARTS_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/cutehmi_charts_pl.ts

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/charts/PointSeries.cpp

HEADERS += \
    src/platform.hpp \
    src/charts/PointSeries.hpp

DISTFILES +=

RESOURCES +=
