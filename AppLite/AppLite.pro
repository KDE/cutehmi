include(../common.pri)

TEMPLATE = app
CONFIG(debug, debug|release) {
    TARGET = AppLite-Debug
}

QT += qml quick

#<workaround id="AppLite-4" target="Qt" cause="bug">
QT += widgets
#</workaround>

# Translations.
TRANSLATIONS = locale/applite_pl.ts

# Resources.
RESOURCES += AppLite.qrc
RC_FILE = AppLite.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../QML

include (../cutehmi_base.pri)

# Default rules for deployment.
include(deployment.pri)

SOURCES += \
    src/main.cpp

HEADERS += \
    src/version.hpp

FORMS +=

DISTFILES += \ 
    deployment.pri \
    AppLite.rc \
    qml/MainWindow.qml \
    qml/DefaultScreen.qml \
    qml/PromptDialog.qml \
    qml/NotificationListView.qml

