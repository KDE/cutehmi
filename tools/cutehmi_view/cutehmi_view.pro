include(../../common.pri)

DESTDIR = $$TOOLS_DESTDIR

TEMPLATE = app
CONFIG(debug, debug|release):TARGET = cutehmi_view_debug
CONFIG(release, debug|release):TARGET = cutehmi_view

QT += qml quick

#<workaround id="cutehmi_view-4" target="Qt" cause="bug">
QT += widgets
#</workaround>

# Translations.
TRANSLATIONS = locale/cutehmi_view_pl.ts

# Resources.
RESOURCES += cutehmi_view.qrc
RC_FILE = cutehmi_view.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../../QML

include(../../modules/cutehmi_1/import.pri)
include(../../modules/cutehmi_xml_1/import.pri)
include(../../modules/cutehmi_app_1/import.pri)

# Default rules for deployment.
include(deployment.pri)

SOURCES += \
    src/main.cpp

HEADERS += \
    src/version.hpp

FORMS +=

DISTFILES += \ 
    deployment.pri \
    cutehmi_view.rc \
    qml/MainWindow.qml \
    qml/DefaultScreen.qml \
    qml/PromptDialog.qml \
    qml/NotificationListView.qml

