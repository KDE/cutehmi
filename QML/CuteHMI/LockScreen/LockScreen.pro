include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_lockscreen_1_qml)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

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
    KeyButton.qml \
    LockScreen.qml \
    LockScreenSettings.qml \
    ChangePasswordWizard.qml \
    LockScreenPopup.qml

RESOURCES +=
