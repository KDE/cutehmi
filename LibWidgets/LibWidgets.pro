include(../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_widgets)

QT += widgets quick quickwidgets

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
    src/widgets/UIVisitorDelegate.cpp \
    src/widgets/AbstractQMLWidgetWrapper.cpp \
    src/widgets/QuickViewWrapper.cpp \
    src/widgets/QuickWidgetWrapper.cpp

HEADERS += \
    src/platform.hpp \
    src/widgets/ErrorBox.hpp \
    src/widgets/UIVisitorDelegate.hpp \
    src/widgets/IUIPlugin.hpp \
    src/widgets/AbstractQMLWidgetWrapper.hpp \
    src/widgets/QuickViewWrapper.hpp \
    src/widgets/QuickWidgetWrapper.hpp

DISTFILES +=

RESOURCES +=
