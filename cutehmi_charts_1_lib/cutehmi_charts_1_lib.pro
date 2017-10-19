include(../common.pri)
include(libdef.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget($$CUTEHMI_CHARTS_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.
VERSION = $$CUTEHMI_CHARTS_LIBVERSION

QT += qml quick

# Configure library for building.
DEFINES += CUTEHMI_CHARTS_BUILD
DEFINES += CUTEHMI_CHARTS_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_CHARTS_LIBNAME}_pl.ts

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
    libdef.pri

RESOURCES +=
