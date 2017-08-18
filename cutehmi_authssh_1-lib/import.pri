# This file sets qmake variables for linkage against cutehmi_authssh_1 library.

include(version.pri)

DEFINES += CUTEHMI_AUTHSSH_1_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
win32:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_authssh_1)$$CUTEHMI_AUTHSSH_1_MAJOR
unix:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_authssh_1)

