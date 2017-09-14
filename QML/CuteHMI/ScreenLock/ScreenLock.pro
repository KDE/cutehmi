include(../../../common.pri)

TEMPLATE = lib
TARGET = $$qtLibraryTarget(cutehmi_screenlock_qml)
DESTDIR = $$PWD/plugins	# QtDesigner can find library only in a location relative to qmldir file.

QT += qml quick

CONFIG += plugin

# Translations.
TRANSLATIONS = locale/cutehmi_screenlock_qml_pl.ts

include(../../../UtilsLib/import.pri)
include(../../../BaseLib/import.pri)

HEADERS += \
    src/CuteHMIScreenLockQMLPlugin.hpp \
    src/cutehmi/screen_lock/LockScreenInterface.hpp

SOURCES += \
    src/CuteHMIScreenLockQMLPlugin.cpp \
    src/cutehmi/screen_lock/LockScreenInterface.cpp

DISTFILES += \ 
    qmldir \
    KeyButton.qml \
    LockScreen.qml

RESOURCES +=
