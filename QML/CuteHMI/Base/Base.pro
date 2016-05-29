include(../../../common.pri)

TEMPLATE = aux	# Setting this to aux to avoid creation of empty binary. Change to lib if some CPP code becomes available.
TARGET = $$qtLibraryTarget(cutehmi_qmlplugin_base)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

CONFIG += plugin

QT += qml quick

# Translations.
TRANSLATIONS = locale/cutehmi_qmlplugin_base_pl.ts

DISTFILES += \
    qmldir \
    TextDisplay.qml \
    designer/Base.metainfo \
    Pipe.qml \
    PipeEmitterSettings.qml \
    PipePoint.qml \
    NumberDisplay.qml

RESOURCES +=

