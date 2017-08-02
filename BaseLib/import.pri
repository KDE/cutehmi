# This file sets qmake variables for linkage against cutehmi_base library.

include(version.pri)

DEFINES += CUTEHMI_BASE_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
win32:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_base)$$CUTEHMI_BASE_MAJOR
unix:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_base)

