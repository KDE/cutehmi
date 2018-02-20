include(../common.pri)
include(libdef.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget($$CUTEHMI_STUPID_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.
VERSION = $$CUTEHMI_STUPID_LIBVERSION

QT -= gui
QT += qml concurrent sql

# Configure the library for building.
DEFINES += CUTEHMI_STUPID_BUILD
DEFINES += CUTEHMI_STUPID_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_STUPID_LIBNAME}_pl.ts

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_1/import.pri)
include(../cutehmi_services_1_lib/import.pri)
include(../cutehmi_charts_1_lib/import.pri)

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
    libdef.pri

RESOURCES +=
