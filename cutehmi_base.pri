# This file sets qmake variables for linkage against cutehmi_base library.
# Note: common.pri must be included before this file.

DEFINES += CUTEHMI_BASE_DYNAMIC
INCLUDEPATH += $$PWD/LibBase/src
DEPENDPATH += $$PWD/LibBase/src
win32:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_base)$$CUTEHMI_BASE_MAJOR
unix:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_base)

