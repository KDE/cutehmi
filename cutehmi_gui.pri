# This file sets qmake variables for linkage against cutehmi_gui library.
# Note: common.pri must be included before this file.

DEFINES += CUTEHMI_GUI_DYNAMIC
INCLUDEPATH += $$PWD/LibGUI/src
DEPENDPATH += $$PWD/LibGUI/src
LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_gui)$$CUTEHMI_GUI_MAJOR
