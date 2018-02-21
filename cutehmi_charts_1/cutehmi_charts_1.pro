include(../common.pri)
include(libdef.pri)

TEMPLATE = lib

TARGET = $$cutehmiTarget($$CUTEHMI_CHARTS_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.

VERSION = $$CUTEHMI_CHARTS_LIBVERSION

#CONFIG += plugin

# Configure the library for building.
DEFINES += CUTEHMI_CHARTS_BUILD
DEFINES += CUTEHMI_CHARTS_DYNAMIC

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_CHARTS_LIBNAME}_pl.ts

QT += qml quick

include(../cutehmi_1/import.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/charts/PointSeries.cpp \
    src/charts/logging.cpp

HEADERS += \
    include/charts/PointSeries.hpp \
    include/charts/internal/platform.hpp \
    include/charts/internal/common.hpp \
    include/charts/logging.hpp

DISTFILES += \
    import.pri \
    libdef.pri

RESOURCES +=
