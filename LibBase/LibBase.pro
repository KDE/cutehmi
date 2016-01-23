include(../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_base)

QT -= gui

# Configure the library for building.
VER_MAJ = $$CUTEHMI_BASE_MAJOR
VER_MIN = 0
VER_PAT = 0
DEFINES += CUTEHMI_BASE_BUILD
DEFINES += CUTEHMI_BASE_DYNAMIC
#CONFIG += dynamic

# Translations.
TRANSLATIONS = locale/cutehmi_base_pl.ts

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/base/ProjectModel.cpp

HEADERS += \
    src/platform.hpp \
    src/utils/NonCopyable.hpp \
    src/utils/NonMovable.hpp \
    src/utils/Singleton.hpp \
    src/base/ProjectModel.hpp \
    src/base/IPLCClientPlugin.hpp
    src/debug/DestructorTest.hpp

DISTFILES +=

RESOURCES +=
