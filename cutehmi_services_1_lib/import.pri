# This file sets qmake variables for linkage against cutehmi_services library.

include(version.pri)

DEFINES += CUTEHMI_SERVICES_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
win32:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_services)$$CUTEHMI_SERVICES_MAJOR
unix:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_services)

