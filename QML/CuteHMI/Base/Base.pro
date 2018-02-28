include(../../../common.pri)

TEMPLATE = lib

DESTDIR = $$QML_DESTDIR/CuteHMI/Base/plugins

TARGET = $$qtLibraryTarget(cutehmi_base_1_qml)

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_base_1_qml_pl.ts

include(../../../cutehmi_1/import.pri)

DISTFILES += \
    qmldir \
    plugins.qmltypes \
    designer/Base.metainfo \
    NumberDisplay.qml \
    Palette.qml \
    ColorSet.qml \
    PropItem.qml \
    Element.qml

RESOURCES +=

HEADERS += \
    src/CuteHMIBaseQMLPlugin.hpp

SOURCES += \
    src/CuteHMIBaseQMLPlugin.cpp

QMAKE_POST_LINK += $$cutehmiCopyFiles($$DISTFILES, $$DESTDIR/..)
