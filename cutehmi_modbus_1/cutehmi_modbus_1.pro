include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_modbus_1
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui
QT += qml

CONFIG += plugin

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_1/import.pri)
include(../cutehmi_services_1_lib/import.pri)
include(../cutehmi_modbus_1_lib/import.pri)
include(../libmodbus.pri)

SOURCES += \
    src/modbus/plugin/ModbusNodeData.cpp \
    src/modbus/plugin/Plugin.cpp \
    src/modbus/plugin/PluginNodeData.cpp \
    src/modbus/plugin/macros.cpp \
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
    src/modbus/internal/macros.cpp \
    src/modbus/internal/RTUConnection.cpp \
    src/modbus/internal/ServiceThread.cpp \
    src/modbus/internal/TCPConnection.cpp

HEADERS += \
    src/modbus/plugin/ModbusNodeData.hpp \
    src/modbus/plugin/Plugin.hpp \
    src/modbus/plugin/PluginNodeData.hpp \
    src/modbus/plugin/macros.hpp \
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
    include/modbus/internal/macros.hpp \
    include/modbus/internal/platform.hpp \
    include/modbus/internal/RegisterTraits.hpp \
    include/modbus/internal/RTUConnection.hpp \
    include/modbus/internal/ServiceThread.hpp \
    include/modbus/internal/TCPConnection.hpp

DISTFILES += cutehmi_modbus_1.json \
    import.pri \
    libdef.pri \
    dev/cutehmi_modbus_1-1.workaround.libmodbus.bug.txt \
    dev/cutehmi_modbus_1-2.workaround.cutehmi_modbus_1_lib.cutehmi_modbus_1_lib-1.txt

RESOURCES += \
    cutehmi_modbus_1.qrc
