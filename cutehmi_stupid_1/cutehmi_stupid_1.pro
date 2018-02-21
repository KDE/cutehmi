include(../common.pri)
include(libdef.pri)

TEMPLATE = lib

TARGET = $$cutehmiTarget($$CUTEHMI_STUPID_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.

VERSION = $$CUTEHMI_STUPID_LIBVERSION

CONFIG += plugin

# Configure the library for building.
DEFINES += CUTEHMI_STUPID_BUILD
DEFINES += CUTEHMI_STUPID_DYNAMIC

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_STUPID_LIBNAME}_pl.ts

QT -= gui
QT += qml sql concurrent


include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_1/import.pri)
include(../cutehmi_services_1/import.pri)
include(../cutehmi_charts_1/import.pri)

SOURCES += \
    src/stupid/plugin/Plugin.cpp \
    src/stupid/plugin/StupidNodeData.cpp \
    src/stupid/plugin/PluginNodeData.cpp \
    src/stupid/Client.cpp \
    src/stupid/DS18B20.cpp \
    src/stupid/DS18B20History.cpp \
    src/stupid/Service.cpp \
    src/stupid/internal/AsyncConnector.cpp \
    src/stupid/internal/CommunicationThread.cpp \
    src/stupid/internal/DatabaseThread.cpp \
    src/stupid/internal/DS18B20HistoryWorker.cpp \
    src/stupid/internal/functions.cpp \
    src/stupid/internal/Worker.cpp \
    src/stupid/logging.cpp

HEADERS += \
    src/stupid/plugin/Plugin.hpp \
    src/stupid/plugin/StupidNodeData.hpp \
    src/stupid/plugin/PluginNodeData.hpp \
    include/stupid/Client.hpp \
    include/stupid/DS18B20.hpp \
    include/stupid/DS18B20History.hpp \
    include/stupid/Service.hpp \
    include/stupid/internal/AsyncConnector.hpp \
    include/stupid/internal/common.hpp \
    include/stupid/internal/CommunicationThread.hpp \
    include/stupid/internal/DatabaseConnectionData.hpp \
    include/stupid/internal/DatabaseThread.hpp \
    include/stupid/internal/DS18B20HistoryWorker.hpp \
    include/stupid/internal/functions.hpp \
    include/stupid/internal/platform.hpp \
    include/stupid/internal/Worker.hpp \
    include/stupid/logging.hpp

DISTFILES += cutehmi_stupid_1.json \
    dev/cutehmi_stupid_1-1.solved.Qt.design.txt \
    import.pri \
    libdef.pri

RESOURCES += \
    cutehmi_stupid_1.qrc
