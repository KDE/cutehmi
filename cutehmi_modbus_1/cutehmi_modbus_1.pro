include(../common.pri)
include(libdef.pri)

TEMPLATE = lib

DESTDIR = $$LIB_DESTDIR

TARGET = $$cutehmiTarget($$CUTEHMI_MODBUS_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.

VERSION = $$CUTEHMI_MODBUS_LIBVERSION

CONFIG += plugin

# Configure the library for building.
DEFINES += CUTEHMI_MODBUS_BUILD
DEFINES += CUTEHMI_MODBUS_DYNAMIC

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_MODBUS_LIBNAME}_pl.ts

QT -= gui
QT += qml concurrent


include(../cutehmi_1/import.pri)
include(../cutehmi_xml_1/import.pri)
include(../cutehmi_services_1/import.pri)
include(../libmodbus.pri)

SOURCES += \
    src/cutehmi/modbus/plugin/ModbusNodeData.cpp \
    src/cutehmi/modbus/plugin/Plugin.cpp \
    src/cutehmi/modbus/plugin/PluginNodeData.cpp \
    src/cutehmi/modbus/AbstractDevice.cpp \
    src/cutehmi/modbus/Client.cpp \
    src/cutehmi/modbus/Coil.cpp \
    src/cutehmi/modbus/DiscreteInput.cpp \
    src/cutehmi/modbus/Exception.cpp \
    src/cutehmi/modbus/HoldingRegister.cpp \
    src/cutehmi/modbus/InputRegister.cpp \
    src/cutehmi/modbus/Service.cpp \
    src/cutehmi/modbus/internal/DummyConnection.cpp \
    src/cutehmi/modbus/internal/functions.cpp \
    src/cutehmi/modbus/internal/LibmodbusConnection.cpp \
    src/cutehmi/modbus/internal/RTUConnection.cpp \
    src/cutehmi/modbus/internal/ServiceThread.cpp \
    src/cutehmi/modbus/internal/TCPConnection.cpp \
    src/cutehmi/modbus/logging.cpp

HEADERS += \
    src/cutehmi/modbus/plugin/ModbusNodeData.hpp \
    src/cutehmi/modbus/plugin/Plugin.hpp \
    src/cutehmi/modbus/plugin/PluginNodeData.hpp \
    include/cutehmi/modbus/AbstractDevice.hpp \
    include/cutehmi/modbus/Client.hpp \
    include/cutehmi/modbus/Coil.hpp \
    include/cutehmi/modbus/DiscreteInput.hpp \
    include/cutehmi/modbus/Exception.hpp \
    include/cutehmi/modbus/HoldingRegister.hpp \
    include/cutehmi/modbus/InputRegister.hpp \
    include/cutehmi/modbus/Service.hpp \
    include/cutehmi/modbus/internal/AbstractConnection.hpp \
    include/cutehmi/modbus/internal/common.hpp \
    include/cutehmi/modbus/internal/DataContainer.hpp \
    include/cutehmi/modbus/internal/DummyConnection.hpp \
    include/cutehmi/modbus/internal/functions.hpp \
    include/cutehmi/modbus/internal/LibmodbusConnection.hpp \
    include/cutehmi/modbus/internal/platform.hpp \
    include/cutehmi/modbus/internal/RegisterTraits.hpp \
    include/cutehmi/modbus/internal/RTUConnection.hpp \
    include/cutehmi/modbus/internal/ServiceThread.hpp \
    include/cutehmi/modbus/internal/TCPConnection.hpp \
    include/cutehmi/modbus/logging.hpp

DISTFILES += cutehmi_modbus_1.json \
    import.pri \
    libdef.pri \
    dev/cutehmi_modbus_1-1.workaround.libmodbus.bug.txt \
    dev/cutehmi_modbus_1-2.workaround.cutehmi_modbus_1.cutehmi_modbus_1-1.txt

RESOURCES += \
    cutehmi_modbus_1.qrc
