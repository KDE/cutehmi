# Common qmake input for all CuteHMI subprojects.

DESTDIR = $$PWD/../bin

CONFIG += object_parallel_to_source

QMAKE_CXXFLAGS += -std=c++11

UI_DIR = $$_PRO_FILE_PWD_/uic
MOC_DIR = $$_PRO_FILE_PWD_/moc
RCC_DIR = $$_PRO_FILE_PWD_/rcc

CONFIG(debug, debug|release) {
    DEFINES += CUTEHMI_DEBUG
}
CONFIG(release, debug|release) {
    DEFINES += CUTEHMI_RELEASE
    DEFINES += QT_NO_DEBUG_OUTPUT
}
