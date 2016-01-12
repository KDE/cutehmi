TEMPLATE = lib
CONFIG += plugin
CONFIG += object_parallel_to_source
QT += qml quick

UI_DIR = $$PWD/uic
MOC_DIR = $$PWD/moc
RCC_DIR = $$PWD/rcc

TARGET = $$qtLibraryTarget(cutehmi_qmlplugin_modbus)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file

#translations
TRANSLATIONS = locale/cutehmi_qmlplugin_modbus_pl.ts

QMAKE_CXXFLAGS += -std=c++11

#cutehmi_base
CUTEHMI_BASE_MAJOR = 0
DEFINES += CUTEHMI_DYNAMIC
INCLUDEPATH += ../../../LibBase/src
DEPENDPATH += ../../../LibBase/src
LIBS += -L$$PWD/../../../../bin -l$$qtLibraryTarget(cutehmi_base)$$CUTEHMI_BASE_MAJOR

HEADERS += \ 
    src/CuteHMIModbusQMLPlugin.hpp

SOURCES += \ 
    src/CuteHMIModbusQMLPlugin.cpp

DISTFILES += \ 
    qmldir \
    HoldingRegisterItem.qml \
    designer/Modbus.metainfo \
    QML_Modbus.qmltypes \
    designer/HoldingRegisterItemSpecifics.qml

RESOURCES +=
