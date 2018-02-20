# This file sets qmake variables for linkage against cutehmi_stupid_1.

include(libdef.pri)

DEFINES += CUTEHMI_STUPID_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
LIBS += -L$$PWD/../../bin -l$$cutehmiTarget($$CUTEHMI_STUPID_LIBNAME)
