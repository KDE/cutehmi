# This file sets qmake variables for linkage against cutehmi_modbus library.
# Note: common.pri must be included before this file.

DEFINES += CUTEHMI_MODBUS_DYNAMIC
INCLUDEPATH += $$PWD/ModbusLib/include
DEPENDPATH += $$PWD/ModbusLib/include
win32:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_modbus)$$CUTEHMI_MODBUS_MAJOR
unix:LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_modbus)

