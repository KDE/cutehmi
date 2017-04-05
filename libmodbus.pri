# This file sets qmake variables for linkage against libmodbus library.
# Note: common.pri must be included before this file.

DEFINES += DLLBUILD
INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
win32:LIBS += -L$$PWD/../lib -llibmodbus-5
unix:LIBS += -L$$PWD/../lib -lmodbus
