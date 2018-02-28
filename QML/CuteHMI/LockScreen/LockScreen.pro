include(../../../common.pri)

TEMPLATE = lib

DESTDIR = $$QML_DESTDIR/CuteHMI/LockScreen/plugins

TARGET = $$qtLibraryTarget(cutehmi_lockscreen_1_qml)

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_lockscreen_1_qml_pl.ts

include(../../../cutehmi_1/import.pri)

HEADERS += \
    src/CuteHMILockScreenQMLPlugin.hpp \
    src/cutehmi/lockscreen/qml/Auth.hpp \
    src/cutehmi/lockscreen/qml/Settings.hpp

SOURCES += \
    src/CuteHMILockScreenQMLPlugin.cpp \
    src/cutehmi/lockscreen/qml/Auth.cpp \
    src/cutehmi/lockscreen/qml/Settings.cpp

DISTFILES += \ 
    qmldir \
    plugins.qmltypes \
    KeyButton.qml \
    LockScreen.qml \
    LockScreenSettings.qml \
    ChangePasswordWizard.qml \
    LockScreenPopup.qml \

RESOURCES +=

QMAKE_POST_LINK += $$cutehmiCopyFiles($$DISTFILES, $$DESTDIR/..)
