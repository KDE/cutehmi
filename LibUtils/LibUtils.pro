include(../common.pri)

TEMPLATE = aux
TARGET = $$qtLibraryTarget(cutehmi_utils)

QT -= core gui

# Configure the library.
VER_MAJ = $$CUTEHMI_UTILS_MAJOR
VER_MIN = 0
VER_PAT = 0

# Translations.
TRANSLATIONS = locale/cutehmi_utils_pl.ts

HEADERS += \
    src/platform.hpp \
    src/utils/NonCopyable.hpp \
    src/utils/NonMovable.hpp \
    src/utils/Singleton.hpp \
    src/utils/DestructorTest.hpp

DISTFILES +=

RESOURCES +=
