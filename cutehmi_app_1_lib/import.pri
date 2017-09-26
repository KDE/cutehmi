# This file sets qmake variables for linkage against cutehmi_app_1 library.

include(libdef.pri)

DEFINES += CUTEHMI_APP_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
win32:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget($$CUTEHMI_APP_LIBNAME)
unix:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget($$CUTEHMI_APP_LIBNAME)
