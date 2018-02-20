# This file sets qmake variables for linkage against cutehmi_authssh_1.

include(libdef.pri)

DEFINES += CUTEHMI_AUTHSSH_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
LIBS += -L$$PWD/../../bin -l$$cutehmiTarget($$CUTEHMI_AUTHSSH_LIBNAME)
