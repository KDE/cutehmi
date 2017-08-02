include(../common.pri)
include(version.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_stupid)

QT -= gui
QT += qml concurrent sql

# Set version.
VER_MAJ = $$CUTEHMI_STUPID_MAJOR
VER_MIN = $$CUTEHMI_STUPID_MINOR
VER_PAT = $$CUTEHMI_STUPID_MICRO

# Configure the library for building.
DEFINES += CUTEHMI_STUPID_BUILD
DEFINES += CUTEHMI_STUPID_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/cutehmi_stupid_pl.ts

include(../UtilsLib/import.pri)
include(../BaseLib/import.pri)
include(../ServicesLib/import.pri)
include(../ChartsLib/import.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/stupid/DS18B20.cpp \
    src/stupid/DS18B20History.cpp \
    src/stupid/internal/macros.cpp \
    src/stupid/internal/CommunicationThread.cpp \
    src/stupid/internal/DatabaseThread.cpp \
    src/stupid/internal/DS18B20HistoryWorker.cpp \
    src/stupid/internal/Worker.cpp \
    src/stupid/Client.cpp \
    src/stupid/Service.cpp \
    src/stupid/internal/AsyncConnector.cpp \
    src/stupid/internal/functions.cpp

HEADERS += \
    include/stupid/internal/platform.hpp \
    include/stupid/internal/common.hpp \
    include/stupid/internal/macros.hpp \
    include/stupid/internal/CommunicationThread.hpp \
    include/stupid/internal/DatabaseConnectionData.hpp \
    include/stupid/internal/DatabaseThread.hpp \
    include/stupid/internal/DS18B20HistoryWorker.hpp \
    include/stupid/internal/Worker.hpp \
    include/stupid/DS18B20.hpp \
    include/stupid/DS18B20History.hpp \
    include/stupid/Client.hpp \
    include/stupid/Service.hpp \
    include/stupid/internal/AsyncConnector.hpp \
    include/stupid/internal/functions.hpp

DISTFILES += \
    import.pri \
    version.pri

RESOURCES +=
