include(../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_modbus)

QT -= gui
QT += qml concurrent

# Configure the library for building
VER_MAJ = $$CUTEHMI_MODBUS_MAJOR
VER_MIN = 0
VER_PAT = 0
DEFINES += CUTEHMI_MODBUS_BUILD
DEFINES += CUTEHMI_MODBUS_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/cutehmi_modbus_pl.ts

include(../cutehmi_base.pri)
include(../cutehmi_services.pri)
include(../libmodbus.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/modbus/Client.cpp \
    src/modbus/Exception.cpp \
    src/modbus/HoldingRegister.cpp \
    src/modbus/InputRegister.cpp \
    src/modbus/Coil.cpp \
    src/modbus/DiscreteInput.cpp \
    src/modbus/Service.cpp \
    src/modbus/internal/macros.cpp \
    src/modbus/internal/DummyConnection.cpp \
    src/modbus/internal/LibmodbusConnection.cpp \
    src/modbus/internal/RTUConnection.cpp \
    src/modbus/internal/TCPConnection.cpp \
    src/modbus/internal/functions.cpp \
    src/modbus/AbstractDevice.cpp \
    src/modbus/internal/ServiceThread.cpp

HEADERS += \
    include/modbus/Client.hpp \
    include/modbus/Coil.hpp \
    include/modbus/DiscreteInput.hpp \
    include/modbus/Exception.hpp \
    include/modbus/HoldingRegister.hpp \
    include/modbus/InputRegister.hpp \
    include/modbus/Service.hpp \
    include/modbus/internal/platform.hpp \
    include/modbus/internal/common.hpp \
    include/modbus/internal/macros.hpp \
    include/modbus/internal/AbstractConnection.hpp \
    include/modbus/internal/DataContainer.hpp \
    include/modbus/internal/RegisterTraits.hpp \
    include/modbus/internal/DummyConnection.hpp \
    include/modbus/internal/LibmodbusConnection.hpp \
    include/modbus/internal/RTUConnection.hpp \
    include/modbus/internal/TCPConnection.hpp \
    include/modbus/internal/functions.hpp \
    include/modbus/AbstractDevice.hpp \
    include/modbus/internal/ServiceThread.hpp

DISTFILES +=

RESOURCES +=

STATECHARTS +=
