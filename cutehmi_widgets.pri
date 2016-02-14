# This file sets qmake variables for linkage against cutehmi_widgets library.
# Note: common.pri must be included before this file.

DEFINES += CUTEHMI_WIDGETS_DYNAMIC
INCLUDEPATH += $$PWD/LibWidgets/src
DEPENDPATH += $$PWD/LibWidgets/src
LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_widgets)$$CUTEHMI_WIDGETS_MAJOR
