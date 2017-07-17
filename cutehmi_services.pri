# This file sets qmake variables for linkage against cutehmi_services library.
# Note: common.pri must be included before this file.

DEFINES += CUTEHMI_SERVICES_DYNAMIC
INCLUDEPATH += $$PWD/ServicesLib/include
DEPENDPATH += $$PWD/ServicesLib/include
win32:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_services)$$CUTEHMI_SERVICES_MAJOR
unix:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_services)
