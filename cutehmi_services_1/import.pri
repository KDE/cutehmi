# This file sets qmake variables for linkage against cutehmi_services_1.

include(libdef.pri)

DEFINES += CUTEHMI_SERVICES_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
LIBS += -L$$PWD/../../bin -l$$cutehmiTarget($$CUTEHMI_SERVICES_LIBNAME)
