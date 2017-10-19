# This file sets qmake variables for linkage against cutehmi_base_1_lib.

include(libdef.pri)

DEFINES += CUTEHMI_BASE_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget($$CUTEHMI_BASE_LIBNAME)
