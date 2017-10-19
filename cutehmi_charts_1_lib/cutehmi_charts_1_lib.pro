include(../common.pri)
include(version.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_charts)

QT += qml quick

# Set version.
VER_MAJ = $$CUTEHMI_CHARTS_MAJOR
VER_MIN = $$CUTEHMI_CHARTS_MINOR
VER_PAT = $$CUTEHMI_CHARTS_MICRO

# Configure library for building.
DEFINES += CUTEHMI_CHARTS_BUILD
DEFINES += CUTEHMI_CHARTS_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/cutehmi_charts_pl.ts

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_base_1_lib/import.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/charts/PointSeries.cpp \
    src/charts/internal/macros.cpp

HEADERS += \
    include/charts/PointSeries.hpp \
    include/charts/internal/platform.hpp \
    include/charts/internal/common.hpp \
    include/charts/internal/macros.hpp

DISTFILES += \
    import.pri \
    version.pri

RESOURCES +=
