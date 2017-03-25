# This file sets qmake variables for linkage against cutehmi_base library.
# Note: common.pri must be included before this file.

include(cutehmi_utils.pri)

DEFINES += CUTEHMI_BASE_DYNAMIC
INCLUDEPATH += $$PWD/LibBase/include
DEPENDPATH += $$PWD/LibBase/include
win32:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_base)$$CUTEHMI_BASE_MAJOR
unix:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_base)

