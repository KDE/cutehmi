include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_qmlplugin_base)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_qmlplugin_base_pl.ts

include(../../../cutehmi_base.pri)

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

