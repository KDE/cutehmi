include(../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_stupid)

QT -= gui
QT += qml concurrent sql

# Configure the library for building
VER_MAJ = $$CUTEHMI_STUPID_MAJOR
VER_MIN = 0
VER_PAT = 0
DEFINES += CUTEHMI_STUPID_BUILD
DEFINES += CUTEHMI_STUPID_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/cutehmi_stupid_pl.ts

include(../cutehmi_base.pri)
include(../cutehmi_charts.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/stupid/Client.cpp \
    src/stupid/NodeDataObject.cpp \
    src/stupid/Service.cpp \
    src/stupid/CommunicationThread.cpp \
    src/stupid/VisitorDelegate.cpp \
    src/stupid/DS18B20.cpp \
    src/stupid/DS18B20History.cpp \
    src/stupid/DS18B20HistoryModel.cpp \
    src/stupid/DatabaseThread.cpp \
    src/stupid/Worker.cpp

HEADERS += \
    src/platform.hpp \
    src/stupid/Client.hpp \
    src/stupid/NodeDataObject.hpp \
    src/stupid/Service.hpp \
    src/stupid/CommunicationThread.hpp \
    src/stupid/VisitorDelegate.hpp \
    src/stupid/DS18B20.hpp \
    src/stupid/DS18B20History.hpp \
    src/stupid/DS18B20HistoryModel.hpp \
    src/stupid/DatabaseThread.hpp \
    src/stupid/DatabaseConnectionData.hpp \
    src/stupid/Worker.hpp

DISTFILES +=

RESOURCES +=
