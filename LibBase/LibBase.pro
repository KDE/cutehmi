TEMPLATE = lib

#todo rename to cutehmi_lib_base (does liblibraryname convention make sense?)
TARGET = $$qtLibraryTarget(cutehmi_base)
DESTDIR = $$PWD/../../bin

QT -= gui
QT += qml

# Configure the library for building
VER_MAJ = 0
VER_MIN = 0
VER_PAT = 0
DEFINES += CUTEHMI_BUILD
DEFINES += CUTEHMI_DYNAMIC
#CONFIG += dynamic

CONFIG += object_parallel_to_source

UI_DIR = $$PWD/uic
MOC_DIR = $$PWD/moc
RCC_DIR = $$PWD/rcc

#translations
TRANSLATIONS = locale/cutehmi_base_pl.ts

QMAKE_CXXFLAGS += -std=c++11

#libmodbus
DEFINES += DLLBUILD
INCLUDEPATH += $$PWD/../../libmodbus-3.1.2/src
DEPENDPATH += $$PWD/../../libmodbus-3.1.2/src
LIBS += -L$$PWD/../../libmodbus-3.1.2/src/.libs -llibmodbus-5

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/modbus/AbstractConnection.cpp \
    src/modbus/Client.cpp \
    src/modbus/ClientPlugin.cpp \
    src/modbus/ConnectionFactory.cpp \
    src/modbus/Exception.cpp \
    src/modbus/HoldingRegister.cpp \
    src/modbus/InputRegister.cpp \
    src/modbus/RTUConnection.cpp \
    src/modbus/TCPConnection.cpp \
    src/base/PLCClientManager.cpp \
    src/modbus/functions.cpp \
    src/base/ProjectModel.cpp

HEADERS += \
    src/platform.hpp \
    src/modbus/AbstractConnection.hpp \
    src/modbus/Client.hpp \
    src/modbus/ClientPlugin.hpp \
    src/modbus/ConnectionFactory.hpp \
    src/modbus/Exception.hpp \
    src/modbus/HoldingRegister.hpp \
    src/modbus/InputRegister.hpp \
    src/modbus/RegisterTraits.hpp \
    src/modbus/RTUConnection.hpp \
    src/modbus/TCPConnection.hpp \
    src/utils/NonCopyable.hpp \
    src/utils/NonMovable.hpp \
    src/utils/Singleton.hpp \
    src/base/PLCClientManager.hpp \
    src/debug/DestructorTest.hpp \
    src/modbus/functions.hpp \
    src/base/ProjectModel.hpp

DISTFILES +=

RESOURCES +=
