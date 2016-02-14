include(../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_widgets)

QT += widgets

# Configure the library for building.
VER_MAJ = $$CUTEHMI_WIDGETS_MAJOR
VER_MIN = 0
VER_PAT = 0
DEFINES += CUTEHMI_WIDGETS_BUILD
DEFINES += CUTEHMI_WIDGETS_DYNAMIC
#CONFIG += dynamic

# Translations.
TRANSLATIONS = locale/cutehmi_widgets_pl.ts

include(../cutehmi_base.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/widgets/ErrorBox.cpp \
    src/widgets/UIVisitorDelegate.cpp

HEADERS += \
    src/platform.hpp \
    src/widgets/ErrorBox.hpp \
    src/widgets/UIVisitorDelegate.hpp \
    src/widgets/IUIPlugin.hpp

DISTFILES +=

RESOURCES +=
