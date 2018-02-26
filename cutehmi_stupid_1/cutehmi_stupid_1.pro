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


include(../cutehmi_1/import.pri)
include(../cutehmi_xml_1/import.pri)
include(../cutehmi_services_1/import.pri)
include(../cutehmi_charts_1/import.pri)

SOURCES += \
    src/cutehmi/stupid/plugin/Plugin.cpp \
    src/cutehmi/stupid/plugin/StupidNodeData.cpp \
    src/cutehmi/stupid/plugin/PluginNodeData.cpp \
    src/cutehmi/stupid/Client.cpp \
    src/cutehmi/stupid/DS18B20.cpp \
    src/cutehmi/stupid/DS18B20History.cpp \
    src/cutehmi/stupid/Service.cpp \
    src/cutehmi/stupid/internal/AsyncConnector.cpp \
    src/cutehmi/stupid/internal/CommunicationThread.cpp \
    src/cutehmi/stupid/internal/DatabaseThread.cpp \
    src/cutehmi/stupid/internal/DS18B20HistoryWorker.cpp \
    src/cutehmi/stupid/internal/functions.cpp \
    src/cutehmi/stupid/internal/Worker.cpp \
    src/cutehmi/stupid/logging.cpp

HEADERS += \
    src/cutehmi/stupid/plugin/Plugin.hpp \
    src/cutehmi/stupid/plugin/StupidNodeData.hpp \
    src/cutehmi/stupid/plugin/PluginNodeData.hpp \
    include/cutehmi/stupid/Client.hpp \
    include/cutehmi/stupid/DS18B20.hpp \
    include/cutehmi/stupid/DS18B20History.hpp \
    include/cutehmi/stupid/Service.hpp \
    include/cutehmi/stupid/internal/AsyncConnector.hpp \
    include/cutehmi/stupid/internal/common.hpp \
    include/cutehmi/stupid/internal/CommunicationThread.hpp \
    include/cutehmi/stupid/internal/DatabaseConnectionData.hpp \
    include/cutehmi/stupid/internal/DatabaseThread.hpp \
    include/cutehmi/stupid/internal/DS18B20HistoryWorker.hpp \
    include/cutehmi/stupid/internal/functions.hpp \
    include/cutehmi/stupid/internal/platform.hpp \
    include/cutehmi/stupid/internal/Worker.hpp \
    include/cutehmi/stupid/logging.hpp

DISTFILES += cutehmi_stupid_1.json \
    dev/cutehmi_stupid_1-1.solved.Qt.design.txt \
    import.pri \
    libdef.pri

RESOURCES += \
    cutehmi_stupid_1.qrc
