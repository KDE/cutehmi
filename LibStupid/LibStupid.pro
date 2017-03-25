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
include(../cutehmi_services.pri)
include(../cutehmi_charts.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/stupid/Client.cpp \
    src/stupid/Service.cpp \
    src/stupid/CommunicationThread.cpp \
    src/stupid/VisitorDelegate.cpp \
    src/stupid/DS18B20.cpp \
    src/stupid/DS18B20History.cpp \
    src/stupid/DatabaseThread.cpp \
    src/stupid/Worker.cpp \
    src/stupid/DS18B20HistoryWorker.cpp \
    src/stupid/StupidNodeData.cpp \
    src/stupid/internal/macros.cpp

HEADERS += \
    include/stupid/internal/platform.hpp \
    include/stupid/Client.hpp \
    include/stupid/CommunicationThread.hpp \
    include/stupid/DatabaseConnectionData.hpp \
    include/stupid/DatabaseThread.hpp \
    include/stupid/DS18B20.hpp \
    include/stupid/DS18B20History.hpp \
    include/stupid/DS18B20HistoryWorker.hpp \
    include/stupid/Service.hpp \
    include/stupid/StupidNodeData.hpp \
    include/stupid/VisitorDelegate.hpp \
    include/stupid/Worker.hpp \
    include/stupid/internal/common.hpp \
    include/stupid/internal/macros.hpp

DISTFILES +=

RESOURCES +=
