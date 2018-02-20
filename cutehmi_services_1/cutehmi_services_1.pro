include(../common.pri)

TEMPLATE = lib
TARGET = cutehmi_services_1
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

SOURCES += \
    src/services/plugin/Plugin.cpp \
    src/services/plugin/PluginNodeData.cpp \
    src/services/Service.cpp \
    src/services/ServiceRegistry.cpp \
    src/services/macros.cpp

HEADERS += \
    src/services/plugin/Plugin.hpp \
    src/services/plugin/PluginNodeData.hpp \
    include/services/Service.hpp \
    include/services/ServiceRegistry.hpp \
    include/services/internal/common.hpp \
    include/services/internal/platform.hpp \
    include/services/macros.hpp

DISTFILES += cutehmi_services_1.json \
    import.pri \
    libdef.pri

RESOURCES += \
    cutehmi_services_1.qrc
