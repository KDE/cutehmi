include(../common.pri)

TEMPLATE = app
CONFIG(debug, debug|release):TARGET = cutehmi_debug
CONFIG(release, debug|release):TARGET = cutehmi

QT += qml quick

#<workaround id="cutehmi_bin_1-4" target="Qt" cause="bug">
QT += widgets
#</workaround>

# Translations.
TRANSLATIONS = locale/cutehmi_bin_1_pl.ts

# Resources.
RESOURCES += cutehmi_bin_1.qrc
RC_FILE = cutehmi_bin_1.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../QML

include(../cutehmi_1/import.pri)
include(../cutehmi_app_1/import.pri)

# Default rules for deployment.
include(deployment.pri)

SOURCES += \
    src/main.cpp

HEADERS += \
    src/version.hpp

FORMS +=

DISTFILES += \ 
    deployment.pri \
    cutehmi_bin_1.rc \
    qml/MainWindow.qml \
    qml/DefaultScreen.qml \
    qml/PromptDialog.qml \
    qml/NotificationListView.qml

