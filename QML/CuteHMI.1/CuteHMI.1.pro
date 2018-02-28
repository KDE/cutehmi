include(../../common.pri)

TEMPLATE = lib

DESTDIR = $$QML_DESTDIR/CuteHMI.1/plugins

TARGET = $$qtLibraryTarget(cutehmi_1_qml)

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_1_qml_pl.ts

include(../../cutehmi_1/import.pri)

DISTFILES += \
    qmldir \
    plugins.qmltypes \
    designer/CuteHMI.metainfo \
    NumberDisplay.qml \
    Palette.qml \
    ColorSet.qml \
    PropItem.qml \
    Element.qml

RESOURCES +=

HEADERS += \
    src/CuteHMIQMLPlugin.hpp

SOURCES += \
    src/CuteHMIQMLPlugin.cpp

QMAKE_POST_LINK += $$cutehmiCopyFiles($$DISTFILES, $$DESTDIR/..)
