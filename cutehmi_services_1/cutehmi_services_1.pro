include(../common.pri)
include(libdef.pri)

TEMPLATE = lib

DESTDIR = $$LIB_DESTDIR

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


include(../cutehmi_1/import.pri)

SOURCES += \
    src/cutehmi/services/plugin/Plugin.cpp \
    src/cutehmi/services/plugin/PluginNodeData.cpp \
    src/cutehmi/services/Service.cpp \
    src/cutehmi/services/ServiceRegistry.cpp \
    src/cutehmi/services/logging.cpp

HEADERS += \
    src/cutehmi/services/plugin/Plugin.hpp \
    src/cutehmi/services/plugin/PluginNodeData.hpp \
    include/cutehmi/services/Service.hpp \
    include/cutehmi/services/ServiceRegistry.hpp \
    include/cutehmi/services/internal/common.hpp \
    include/cutehmi/services/internal/platform.hpp \
    include/cutehmi/services/logging.hpp

DISTFILES += cutehmi_services_1.json \
    import.pri \
    libdef.pri

RESOURCES += \
    cutehmi_services_1.qrc
