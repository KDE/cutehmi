# This file sets qmake variables for linkage against libmodbus library.

DEFINES += DLLBUILD
INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
win32:LIBS += -L$$PWD/../lib -llibmodbus-5
unix:LIBS += -L$$PWD/../lib -lmodbus
