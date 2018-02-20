# This file sets qmake variables for linkage against cutehmi_stupid_1_lib.

include(libdef.pri)

DEFINES += CUTEHMI_STUPID_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget($$CUTEHMI_STUPID_LIBNAME)
