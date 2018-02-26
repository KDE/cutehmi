include(../common.pri)
include(libdef.pri)

TEMPLATE = lib

TARGET = $$cutehmiTarget($$CUTEHMI_XML_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.

VERSION = $$CUTEHMI_XML_LIBVERSION

CONFIG += plugin

# Configure the library for building.
DEFINES += CUTEHMI_XML_BUILD
DEFINES += CUTEHMI_XML_DYNAMIC

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_XML_LIBNAME}_pl.ts

QT -= gui
QT += qml

include(../cutehmi_1/import.pri)

SOURCES += \
    src/cutehmi/xml/conversions.cpp \
    src/cutehmi/xml/ParseAttribute.cpp \
    src/cutehmi/xml/ParseElement.cpp \
    src/cutehmi/xml/ParseHelper.cpp \
    src/cutehmi/xml/internal/functions.cpp \
    src/cutehmi/xml/logging.cpp \
    src/cutehmi/xml/ProjectBackend.cpp \
    src/cutehmi/xml/BackendPlugin.cpp

HEADERS += \
    include/cutehmi/xml/conversions.hpp \
    include/cutehmi/xml/ParseAttribute.hpp \
    include/cutehmi/xml/ParseElement.hpp \
    include/cutehmi/xml/ParseHelper.hpp \
    include/cutehmi/xml/internal/functions.hpp \
    include/cutehmi/xml/internal/common.hpp \
    include/cutehmi/xml/internal/platform.hpp \
    include/cutehmi/xml/logging.hpp \
    include/cutehmi/xml/ProjectBackend.hpp \
    include/cutehmi/xml/IBackendPlugin.hpp \
    include/cutehmi/xml/BackendPlugin.hpp

DISTFILES += cutehmi_app_1.json \
    import.pri \
    libdef.pri \

RESOURCES +=
