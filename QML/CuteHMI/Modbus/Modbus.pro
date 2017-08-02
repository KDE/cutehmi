include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_modbus_qml)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_modbus_qml_pl.ts

include(../../../UtilsLib/import.pri)
include(../../../BaseLib/import.pri)
include(../../../ModbusLib/import.pri)

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
    designer/Modbus.metainfo \
    QML_Modbus.qmltypes \
    CoilItem.qml \
    DiscreteInputItem.qml \
    HoldingRegisterItem.qml \
    InputRegisterItem.qml \
    HoldingRegisterItem.js \
    CoilItem.js

RESOURCES +=
