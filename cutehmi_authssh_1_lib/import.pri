# This file sets qmake variables for linkage against cutehmi_authssh_1 library.

include(libdef.pri)

DEFINES += CUTEHMI_AUTHSSH_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
win32:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget($$CUTEHMI_AUTHSSH_LIBNAME)
unix:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget($$CUTEHMI_AUTHSSH_LIBNAME)
