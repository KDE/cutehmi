# This file sets qmake variables for linkage against libssh library.

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
win32:LIBS += -L$$PWD/../lib -llibssh
unix:LIBS += -L$$PWD/../lib -lssh
