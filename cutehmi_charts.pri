# This file sets qmake variables for linkage against cutehmi_charts library.
# Note: common.pri must be included before this file.

DEFINES += CUTEHMI_CHARTS_DYNAMIC
INCLUDEPATH += $$PWD/LibCharts/src
DEPENDPATH += $$PWD/LibCharts/src
win32:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_charts)$$CUTEHMI_CHARTS_MAJOR
unix:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_charts)
