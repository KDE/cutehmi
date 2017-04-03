# This file sets qmake variables for linkage against cutehmi_stupid library.
# Note: common.pri must be included before this file.

DEFINES += CUTEHMI_STUPID_DYNAMIC
INCLUDEPATH += $$PWD/LibStupid/include
DEPENDPATH += $$PWD/LibStupid/include
win32:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_stupid)$$CUTEHMI_MODBUS_MAJOR
unix:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_stupid)
