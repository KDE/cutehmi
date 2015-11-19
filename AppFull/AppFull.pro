TEMPLATE = app

QT += qml quick widgets quickwidgets

CONFIG += object_parallel_to_source

UI_DIR = $$PWD/uic
MOC_DIR = $$PWD/moc
RCC_DIR = $$PWD/rcc

QMAKE_CXXFLAGS += -std=c++11

#libcutehmibase
LIBCUTEHMIBASE_MAJOR = 0
DEFINES += CUTEHMI_DYNAMIC
INCLUDEPATH += ../LibBase/src
DEPENDPATH += ../LibBase/src
CONFIG(debug, debug|release) {
    LIBS += -L$$OUT_PWD/../LibBase/debug -llibcutehmibase$$LIBCUTEHMIBASE_MAJOR
} else {
    LIBS += -L$$OUT_PWD/../LibBase/release -llibcutehmibase$$LIBCUTEHMIBASE_MAJOR
}

#libmodbus
DEFINES += DLLBUILD
INCLUDEPATH += $$OUT_PWD/../../libmodbus-3.1.2/src
DEPENDPATH += $$OUT_PWD/../../libmodbus-3.1.2/src
LIBS += -L$$OUT_PWD/../../libmodbus-3.1.2/src/.libs -llibmodbus-5

#translations
TRANSLATIONS = locale/appfull_pl.ts

#resources
RESOURCES += AppFull.qrc
RESOURCES += ../LibBase/LibBase.qrc
RC_FILE = AppFull.rc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../LibBase/qml

# Default rules for deployment.
include(deployment.pri)

SOURCES += \
    src/modbus/ClientControlWidget.cpp \
    src/modbus/ConfigurationDialog.cpp \
    src/modbus/ControlWidget.cpp \
    src/DeviceCommunicationDispatcher.cpp \
    src/DevicePoint.cpp \
    src/main.cpp \
    src/MainWindow.cpp \
    src/MessageArea.cpp \
    src/MessageEvent.cpp \
    src/MessageHandler.cpp \
    src/SmartStatusBar.cpp \
    src/Settings.cpp

HEADERS += \ 
    src/version.hpp \
    src/modbus/ClientControlWidget.hpp \
    src/modbus/ConfigurationDialog.hpp \
    src/modbus/ControlWidget.hpp \
    src/DeviceCommunicationDispatcher.hpp \
    src/DevicePoint.hpp \
    src/MainWindow.hpp \
    src/MessageArea.hpp \
    src/MessageEvent.hpp \
    src/MessageHandler.hpp \
    src/SmartStatusBar.hpp \
    src/Settings.hpp

FORMS += \ 
    ui/MainWindow.ui \
    src/modbus/ConfigurationDialog.ui \
    src/modbus/ClientControlWidget.ui

DISTFILES += \ 
    deployment.pri \
    AppFull.rc \
    qml/MainForm.ui.qml

