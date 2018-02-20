# This file sets qmake variables for linkage against cutehmi_charts_1_lib.

include(libdef.pri)

DEFINES += CUTEHMI_CHARTS_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget($$CUTEHMI_CHARTS_LIBNAME)
