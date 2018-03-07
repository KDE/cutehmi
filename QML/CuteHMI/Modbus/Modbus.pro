include(../../../common.pri)

TEMPLATE = lib

DESTDIR = $$QML_DESTDIR/CuteHMI/Modbus/plugins

TARGET = $$qtLibraryTarget(cutehmi_modbus_1_qml)

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_modbus_1_qml_pl.ts

include(../../../modules/cutehmi_1/import.pri)
include(../../../modules/cutehmi_modbus_1/import.pri)

HEADERS += \
    src/CuteHMIModbusQMLPlugin.hpp \
    src/cutehmi/modbus/qml/HoldingRegisterController.hpp \
    src/cutehmi/modbus/qml/CoilController.hpp \
    src/cutehmi/modbus/qml/DiscreteInputController.hpp \
    src/cutehmi/modbus/qml/InputRegisterController.hpp

SOURCES += \
    src/CuteHMIModbusQMLPlugin.cpp \
    src/cutehmi/modbus/qml/HoldingRegisterController.cpp \
    src/cutehmi/modbus/qml/CoilController.cpp \
    src/cutehmi/modbus/qml/DiscreteInputController.cpp \
    src/cutehmi/modbus/qml/InputRegisterController.cpp

DISTFILES += \ 
    qmldir \
    plugins.qmltypes \
    CoilItem.qml \
    DiscreteInputItem.qml \
    HoldingRegisterItem.qml \
    InputRegisterItem.qml \
    HoldingRegisterItem.js \
    CoilItem.js \
    designer/Modbus.metainfo \
    designer/CoilItemSpecifics.qml \
    designer/DiscreteInputItemSpecifics.qml \
    designer/HoldingRegisterItemSpecifics.qml \
    designer/InputRegisterItemSpecifics.qml

RESOURCES +=

QMAKE_POST_LINK += $$cutehmiCopyFiles($$DISTFILES, $$DESTDIR/..)
