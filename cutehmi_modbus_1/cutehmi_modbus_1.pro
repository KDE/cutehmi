include(../common.pri)
include(libdef.pri)

TEMPLATE = lib

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


include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_1/import.pri)
include(../cutehmi_services_1/import.pri)
include(../libmodbus.pri)

SOURCES += \
    src/modbus/plugin/ModbusNodeData.cpp \
    src/modbus/plugin/Plugin.cpp \
    src/modbus/plugin/PluginNodeData.cpp \
    src/modbus/AbstractDevice.cpp \
    src/modbus/Client.cpp \
    src/modbus/Coil.cpp \
    src/modbus/DiscreteInput.cpp \
    src/modbus/Exception.cpp \
    src/modbus/HoldingRegister.cpp \
    src/modbus/InputRegister.cpp \
    src/modbus/Service.cpp \
    src/modbus/internal/DummyConnection.cpp \
    src/modbus/internal/functions.cpp \
    src/modbus/internal/LibmodbusConnection.cpp \
    src/modbus/internal/RTUConnection.cpp \
    src/modbus/internal/ServiceThread.cpp \
    src/modbus/internal/TCPConnection.cpp \
    src/modbus/logging.cpp

HEADERS += \
    src/modbus/plugin/ModbusNodeData.hpp \
    src/modbus/plugin/Plugin.hpp \
    src/modbus/plugin/PluginNodeData.hpp \
    include/modbus/AbstractDevice.hpp \
    include/modbus/Client.hpp \
    include/modbus/Coil.hpp \
    include/modbus/DiscreteInput.hpp \
    include/modbus/Exception.hpp \
    include/modbus/HoldingRegister.hpp \
    include/modbus/InputRegister.hpp \
    include/modbus/Service.hpp \
    include/modbus/internal/AbstractConnection.hpp \
    include/modbus/internal/common.hpp \
    include/modbus/internal/DataContainer.hpp \
    include/modbus/internal/DummyConnection.hpp \
    include/modbus/internal/functions.hpp \
    include/modbus/internal/LibmodbusConnection.hpp \
    include/modbus/internal/platform.hpp \
    include/modbus/internal/RegisterTraits.hpp \
    include/modbus/internal/RTUConnection.hpp \
    include/modbus/internal/ServiceThread.hpp \
    include/modbus/internal/TCPConnection.hpp \
    include/modbus/logging.hpp

DISTFILES += cutehmi_modbus_1.json \
    import.pri \
    libdef.pri \
    dev/cutehmi_modbus_1-1.workaround.libmodbus.bug.txt \
    dev/cutehmi_modbus_1-2.workaround.cutehmi_modbus_1.cutehmi_modbus_1-1.txt

RESOURCES += \
    cutehmi_modbus_1.qrc
