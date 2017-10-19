# This file sets qmake variables for linkage against cutehmi_stupid library.

include(version.pri)

DEFINES += CUTEHMI_STUPID_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
win32:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_stupid)$$CUTEHMI_STUPID_MAJOR
unix:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_stupid)

