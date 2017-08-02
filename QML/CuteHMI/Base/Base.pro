include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_base_qml)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_base_qml_pl.ts

include(../../../UtilsLib/import.pri)
include(../../../BaseLib/import.pri)

DISTFILES += \
    qmldir \
    TextDisplay.qml \
    designer/Base.metainfo \
    Pipe.qml \
    PipeEmitterSettings.qml \
    PipePoint.qml \
    NumberDisplay.qml \
    ValueRangeColor.qml \
    ValueColor.qml \
    Palette.qml \
    ValueRangeColor.js

RESOURCES +=

HEADERS += \
    src/CuteHMIBaseQMLPlugin.hpp

SOURCES += \
    src/CuteHMIBaseQMLPlugin.cpp

