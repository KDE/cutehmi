include(../common.pri)
include(libdef.pri)

TEMPLATE = aux
TARGET = $$qtLibraryTarget($$CUTEHMI_UTILS_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.
VERSION = $$CUTEHMI_UTILS_LIBVERSION

QT -= core gui

# Translations.
TRANSLATIONS = locale/cutehmi_utils_pl.ts

HEADERS += \
    include/utils/DestructorTest.hpp \
    include/utils/NonCopyable.hpp \
    include/utils/NonMovable.hpp \
    include/utils/Singleton.hpp \
    include/utils/MPtr.hpp

DISTFILES += \
    import.pri \
    libdef.pri

RESOURCES +=
