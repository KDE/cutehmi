TEMPLATE = aux	# Setting this to aux to avoid creation of empty binary. Change to lib if some CPP code becomes available.
CONFIG += plugin
CONFIG += object_parallel_to_source
QT += qml quick

UI_DIR = $$PWD/uic
MOC_DIR = $$PWD/moc
RCC_DIR = $$PWD/rcc

TARGET = $$qtLibraryTarget(cutehmi_qmlplugin_base)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file

#translations
TRANSLATIONS = locale/cutehmi_qmlplugin_base_pl.ts

QMAKE_CXXFLAGS += -std=c++11

DISTFILES += \
    qmldir \
    TextDisplay.qml \
    designer/Base.metainfo

RESOURCES +=

