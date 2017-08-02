# This file sets qmake variables for linkage against cutehmi_charts library.

include(version.pri)

DEFINES += CUTEHMI_CHARTS_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
win32:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_charts)$$CUTEHMI_CHARTS_MAJOR
unix:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_charts)

