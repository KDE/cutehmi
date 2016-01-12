TEMPLATE = app

DESTDIR = $$PWD/../../bin
CONFIG(debug, debug|release) {
    TARGET = AppFull-Debug
}

QT += qml quick widgets quickwidgets

CONFIG += object_parallel_to_source

UI_DIR = $$PWD/uic
MOC_DIR = $$PWD/moc
RCC_DIR = $$PWD/rcc

QMAKE_CXXFLAGS += -std=c++11

#cutehmi_base
CUTEHMI_BASE_MAJOR = 0
DEFINES += CUTEHMI_DYNAMIC
INCLUDEPATH += ../LibBase/src
DEPENDPATH += ../LibBase/src
LIBS += -L$$PWD/../../bin -l$$qtLibraryTarget(cutehmi_base)$$CUTEHMI_BASE_MAJOR

#translations
TRANSLATIONS = locale/appfull_pl.ts

#resources
RESOURCES += AppFull.qrc
RC_FILE = AppFull.rc


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../QML

# Default rules for deployment.
include(deployment.pri)

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/MessageArea.cpp \
    src/MessageEvent.cpp \
    src/MessageHandler.cpp \
    src/SmartStatusBar.cpp \
    src/Settings.cpp \
    src/modbus/widgets/ClientControlWidget.cpp \
    src/PLCWidgetFactory.cpp

HEADERS += \ 
    src/version.hpp \
    src/MainWindow.hpp \
    src/MessageArea.hpp \
    src/MessageEvent.hpp \
    src/MessageHandler.hpp \
    src/SmartStatusBar.hpp \
    src/Settings.hpp \
    src/modbus/widgets/ClientControlWidget.hpp \
    src/PLCWidgetFactory.hpp

FORMS += \ 
    ui/MainWindow.ui \
    src/modbus/widgets/ClientControlWidget.ui

DISTFILES += \ 
    deployment.pri \
    AppFull.rc

