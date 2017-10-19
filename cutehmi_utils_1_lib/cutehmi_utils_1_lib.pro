include(../common.pri)
include(version.pri)

TEMPLATE = aux
TARGET = $$qtLibraryTarget(cutehmi_utils_1_lib)

QT -= core gui

# Set version.
VER_MAJ = $$CUTEHMI_UTILS_MAJOR
VER_MIN = $$CUTEHMI_UTILS_MINOR
VER_PAT = $$CUTEHMI_UTILS_MICRO

# Translations.
TRANSLATIONS = locale/cutehmi_utils_pl.ts

HEADERS += \
    include/utils/DestructorTest.hpp \
    include/utils/NonCopyable.hpp \
    include/utils/NonMovable.hpp \
    include/utils/Singleton.hpp \
    include/utils/MPtr.hpp \
    include/utils/macros.hpp

DISTFILES += \
    import.pri \
    version.pri

RESOURCES +=
