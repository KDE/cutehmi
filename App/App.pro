include(../common.pri)

TEMPLATE = app
CONFIG(debug, debug|release) {
    TARGET = App-Debug
}

QT += qml quick

#<workaround id="App-4" target="Qt" cause="bug">
QT += widgets
#</workaround>

# Translations.
TRANSLATIONS = locale/app_pl.ts

# Resources.
RESOURCES += App.qrc
RC_FILE = App.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../QML

include(../UtilsLib/import.pri)
include(../BaseLib/import.pri)

# Default rules for deployment.
include(deployment.pri)

SOURCES += \
    src/main.cpp

HEADERS += \
    src/version.hpp

FORMS +=

DISTFILES += \ 
    deployment.pri \
    App.rc \
    qml/MainWindow.qml \
    qml/DefaultScreen.qml \
    qml/PromptDialog.qml \
    qml/NotificationListView.qml

