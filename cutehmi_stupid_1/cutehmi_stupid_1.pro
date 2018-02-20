include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_stupid_1
# Instead of using $$qtLibraryTarget, for consistent naming of plugins on all platforms add "d" suffix to debug build.
CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,d)
}
DESTDIR = $$DESTDIR/plugins

QT -= gui
QT += qml sql

CONFIG += plugin

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_1/import.pri)
include(../cutehmi_services_1_lib/import.pri)
include(../cutehmi_charts_1_lib/import.pri)
include(../cutehmi_stupid_1_lib/import.pri)

SOURCES += \
    src/stupid/plugin/Plugin.cpp \
    src/stupid/plugin/StupidNodeData.cpp \
    src/stupid/plugin/PluginNodeData.cpp \
    src/stupid/macros.cpp \
    src/stupid/Client.cpp \
    src/stupid/DS18B20.cpp \
    src/stupid/DS18B20History.cpp \
    src/stupid/Service.cpp \
    src/stupid/internal/AsyncConnector.cpp \
    src/stupid/internal/CommunicationThread.cpp \
    src/stupid/internal/DatabaseThread.cpp \
    src/stupid/internal/DS18B20HistoryWorker.cpp \
    src/stupid/internal/functions.cpp \
    src/stupid/internal/Worker.cpp

HEADERS += \
    src/stupid/plugin/Plugin.hpp \
    src/stupid/plugin/StupidNodeData.hpp \
    src/stupid/plugin/PluginNodeData.hpp \
    include/stupid/Client.hpp \
    include/stupid/DS18B20.hpp \
    include/stupid/DS18B20History.hpp \
    include/stupid/macros.hpp \
    include/stupid/Service.hpp \
    include/stupid/internal/AsyncConnector.hpp \
    include/stupid/internal/common.hpp \
    include/stupid/internal/CommunicationThread.hpp \
    include/stupid/internal/DatabaseConnectionData.hpp \
    include/stupid/internal/DatabaseThread.hpp \
    include/stupid/internal/DS18B20HistoryWorker.hpp \
    include/stupid/internal/functions.hpp \
    include/stupid/internal/platform.hpp \
    include/stupid/internal/Worker.hpp

DISTFILES += cutehmi_stupid_1.json \
    dev/cutehmi_stupid_1-1.solved.Qt.design.txt

RESOURCES += \
    cutehmi_stupid_1.qrc
