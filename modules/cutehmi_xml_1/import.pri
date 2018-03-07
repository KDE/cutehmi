# This file sets qmake variables for linkage against cutehmi_xml_1.

include(libdef.pri)

DEFINES += CUTEHMI_XML_DYNAMIC
INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
LIBS += -L$$PWD/../../../bin -l$$cutehmiTarget($$CUTEHMI_XML_LIBNAME)
