TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += src/main.cpp

DEFINES += DLLBUILD

INCLUDEPATH += $$PWD/../../../libmodbus-3.1.2/src
DEPENDPATH += $$PWD/../../../libmodbus-3.1.2/src
LIBS += -L$$PWD/../../../libmodbus-3.1.2/src/.libs -llibmodbus-5

include(deployment.pri)
qtcAddDeployment()
