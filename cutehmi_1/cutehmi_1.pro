include(../common.pri)
include(libdef.pri)

TEMPLATE = lib

TARGET = $$cutehmiTarget($$CUTEHMI_LIBNAME)
win32:TARGET_EXT = .dll # Remove major version number appended to target dll on Windows.

VERSION = $$CUTEHMI_LIBVERSION

#CONFIG += plugin

# Configure the library for building.
DEFINES += CUTEHMI_BUILD
DEFINES += CUTEHMI_DYNAMIC
#CONFIG += shared

# Translations.
TRANSLATIONS = locale/$${CUTEHMI_LIBNAME}_pl.ts

QT -= gui
QT += qml

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/cutehmi/ProjectModel.cpp \
    src/cutehmi/Error.cpp \
    src/cutehmi/Project.cpp \
    src/cutehmi/CuteHMI.cpp \
    src/cutehmi/Exception.cpp \
    src/cutehmi/ErrorException.cpp \
    src/cutehmi/ErrorInfo.cpp \
    src/cutehmi/ProjectNode.cpp \
    src/cutehmi/Plugin.cpp \
    src/cutehmi/internal/PluginNodeData.cpp \
    src/cutehmi/DataBlock.cpp \
    src/cutehmi/PopupBridge.cpp \
    src/cutehmi/Prompt.cpp \
    src/cutehmi/Notification.cpp \
    src/cutehmi/NotificationManager.cpp \
    src/cutehmi/NotificationListModel.cpp \
    src/cutehmi/ProjectNodeData.cpp \
    src/cutehmi/Worker.cpp \
    src/cutehmi/logging.cpp \
    src/cutehmi/ProjectPluginLoader.cpp \
    src/cutehmi/internal/PluginLoader.cpp

HEADERS += \
    include/cutehmi/ProjectModel.hpp \
    include/cutehmi/Error.hpp \
    include/cutehmi/ErrorInfo.hpp \
    include/cutehmi/Project.hpp \
    include/cutehmi/CuteHMI.hpp \
    include/cutehmi/Exception.hpp \
    include/cutehmi/ErrorException.hpp \
    include/cutehmi/internal/common.hpp \
    include/cutehmi/internal/platform.hpp \
    include/cutehmi/Plugin.hpp \
    include/cutehmi/IPlugin.hpp \
    include/cutehmi/internal/PluginNodeData.hpp \
    include/cutehmi/DataBlock.hpp \
    include/cutehmi/ExceptionMixin.hpp \
    include/cutehmi/PopupBridge.hpp \
    include/cutehmi/Prompt.hpp \
    include/cutehmi/Notification.hpp \
    include/cutehmi/NotificationManager.hpp \
    include/cutehmi/NotificationListModel.hpp \
    include/cutehmi/ProjectNodeData.hpp \
    include/cutehmi/Worker.hpp \
    include/cutehmi/logging.hpp \
    include/cutehmi/loggingMacros.hpp \
    include/cutehmi/MPtr.hpp \
    include/cutehmi/NonCopyable.hpp \
    include/cutehmi/NonMovable.hpp \
    include/cutehmi/Singleton.hpp \
    include/cutehmi/IProjectBackend.hpp \
    include/cutehmi/ProjectPluginLoader.hpp \
    include/cutehmi/internal/PluginLoader.hpp \
    include/cutehmi/ProjectNode.hpp

DISTFILES += \
    import.pri \
    libdef.pri \
    dev/cutehmi_1-1.workaround.Qt.design.txt \
    dev/cutehmi_1-2.workaround.std.design.txt

RESOURCES +=
