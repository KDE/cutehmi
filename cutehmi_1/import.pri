# This file sets qmake variables for linkage against cutehmi_1.

include(libdef.pri)

DEFINES += CUTEHMI_BASE_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
LIBS += -L$$PWD/../../bin -l$$cutehmiTarget($$CUTEHMI_BASE_LIBNAME)
