include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_qmlplugin_modbus)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_qmlplugin_modbus_pl.ts

include(../../../cutehmi_base.pri)
include(../../../cutehmi_modbus.pri)

HEADERS += \
    src/CuteHMIModbusQMLPlugin.hpp

SOURCES += \
    src/CuteHMIModbusQMLPlugin.cpp

DISTFILES += \ 
    qmldir \
    HoldingRegisterItem.qml \
    designer/Modbus.metainfo \
    QML_Modbus.qmltypes \
    designer/HoldingRegisterItemSpecifics.qml \
    InputRegisterItem.qml \
    CoilItem.qml \
    DiscreteInputItem.qml \
    designer/InputRegisterItemSpecifics.qml \
    designer/CoilItemSpecifics.qml \
    designer/DiscreteInputItemSpecifics.qml \
    ExtBusyIndicator.qml

RESOURCES +=
