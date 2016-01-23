include(../common.pri)

TEMPLATE = app
CONFIG(debug, debug|release) {
    TARGET = AppFull-Debug
}

QT += qml quick widgets quickwidgets

# Translations.
TRANSLATIONS = locale/appfull_pl.ts

# Resources.
RESOURCES += AppFull.qrc
RC_FILE = AppFull.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../QML

# cutehmi_base
include (../base.pri)

# @todo remove after modbus plugins are ready, for now temporary link with the cutehmi_modbus library.
# cutehmi_modbus
include (../modbus.pri)

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
    src/PLCWidgetFactory.cpp \
    src/RecentFiles.cpp \
    src/modbus/ui/ClientControlWidget.cpp

HEADERS += \ 
    src/version.hpp \
    src/MainWindow.hpp \
    src/MessageArea.hpp \
    src/MessageEvent.hpp \
    src/MessageHandler.hpp \
    src/SmartStatusBar.hpp \
    src/Settings.hpp \
    src/PLCWidgetFactory.hpp \
    src/RecentFiles.hpp \
    src/modbus/ui/ClientControlWidget.hpp

FORMS += \ 
    ui/MainWindow.ui \
    src/modbus/ui/ClientControlWidget.ui

DISTFILES += \ 
    deployment.pri \
    AppFull.rc

