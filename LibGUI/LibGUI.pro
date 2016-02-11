include(../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_gui)

# Configure the library for building.
VER_MAJ = $$CUTEHMI_GUI_MAJOR
VER_MIN = 0
VER_PAT = 0
DEFINES += CUTEHMI_GUI_BUILD
DEFINES += CUTEHMI_GUI_DYNAMIC
#CONFIG += dynamic

# Translations.
TRANSLATIONS = locale/cutehmi_gui_pl.ts

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \

HEADERS += \
    src/gui/messagebox.hpp

DISTFILES +=

RESOURCES +=
