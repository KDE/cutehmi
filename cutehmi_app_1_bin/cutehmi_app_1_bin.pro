include(../common.pri)

TEMPLATE = app
CONFIG(debug, debug|release) {
    TARGET = App-Debug
}

QT += qml quick

#<workaround id="cutehmi_app_1_bin-4" target="Qt" cause="bug">
QT += widgets
#</workaround>

# Translations.
TRANSLATIONS = locale/cutehmi_app_1_bin_pl.ts

# Resources.
RESOURCES += cutehmi_app_1_bin.qrc
RC_FILE = cutehmi_app_1_bin.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../QML

include(../cutehmi_utils_1_lib/import.pri)
include(../cutehmi_base_1_lib/import.pri)
include(../cutehmi_app_1_lib/import.pri)

# Default rules for deployment.
include(deployment.pri)

SOURCES += \
    src/main.cpp

HEADERS += \
    src/version.hpp

FORMS +=

DISTFILES += \ 
    deployment.pri \
    cutehmi_app_1_bin.rc \
    qml/MainWindow.qml \
    qml/DefaultScreen.qml \
    qml/PromptDialog.qml \
    qml/NotificationListView.qml

