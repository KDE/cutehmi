# This file sets qmake variables for linkage against cutehmi_modbus library.
# Note: common.pri must be included before this file.

DEFINES += CUTEHMI_MODBUS_DYNAMIC
INCLUDEPATH += $$PWD/LibModbus/src
DEPENDPATH += $$PWD/LibModbus/src
LIBS += -L$$PWD/../bin -l$$qtLibraryTarget(cutehmi_modbus)$$CUTEHMI_MODBUS_MAJOR
