# Common qmake input for all CuteHMI subprojects.

TOOLS_DESTDIR = $$PWD/../bin
MODULES_DESTDIR = $$PWD/../bin
QML_DESTDIR = $$PWD/../QML

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

DEFINES += QT_DEPRECATED_WARNINGS

# Returns affected library target name.
# This function is intended to be used instead of standard $$qtLibraryTarget. It adds "d" suffix to debug build on all platforms (for consistent naming).
defineReplace(cutehmiTarget) {
    target = $$1
    CONFIG(debug, debug|release) {
        target = $$join(target,,,d)
    }
    return($$target)
}

# Prepare a string that copies files to specified directory. Usage: '$$cutehmiCopyFiles($$files, $$dir)'.
defineReplace(cutehmiCopyFiles) {
    result =
    for(FILE, 1) {
        src = $$PWD/$$FILE
        dst = $$2/$$FILE
        dstDir = $$dirname(dst)

        # Replace slashes in paths with backslashes for Windows
        win32:src ~= s,/,\\,g
        win32:dst ~= s,/,\\,g
        win32:dstDir ~= s,/,\\,g

        result += $$QMAKE_MKDIR $$quote($$dstDir) $$escape_expand(\\n\\t)
        result += $$QMAKE_COPY $$quote($$src) $$quote($$dst) $$escape_expand(\\n\\t)
    }
    return($$result)
}
