# This file sets qmake variables for linkage against cutehmi_modbus library.

include(version.pri)

DEFINES += CUTEHMI_MODBUS_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
win32:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_modbus)$$CUTEHMI_MODBUS_MAJOR
unix:LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_modbus)

