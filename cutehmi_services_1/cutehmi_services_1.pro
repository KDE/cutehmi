include(../common.pri)
include(libdef.pri)

TEMPLATE = lib

TARGET = $$cutehmiTarget($$CUTEHMI_SERVICES_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.

VERSION = $$CUTEHMI_SERVICES_LIBVERSION

CONFIG += plugin

# Configure the library for building.
DEFINES += CUTEHMI_SERVICES_BUILD
DEFINES += CUTEHMI_SERVICES_DYNAMIC

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_SERVICES_LIBNAME}_pl.ts

QT -= gui
QT += qml


include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_1/import.pri)
include(../cutehmi_services_1/import.pri)

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
