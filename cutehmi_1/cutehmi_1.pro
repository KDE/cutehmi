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

include(../cutehmi_utils_1_lib/import.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

SOURCES += \
    src/cutehmi/ProjectModel.cpp \
    src/cutehmi/Error.cpp \
    src/cutehmi/PluginLoader.cpp \
    src/cutehmi/Project.cpp \
    src/cutehmi/CuteHMI.cpp \
    src/cutehmi/internal/ProjectXMLBackend.cpp \
    src/cutehmi/Exception.cpp \
    src/cutehmi/ErrorException.cpp \
    src/cutehmi/ErrorInfo.cpp \
    src/cutehmi/ProjectNode.cpp \
    src/cutehmi/Plugin.cpp \
    src/cutehmi/xml/ParseAttribute.cpp \
    src/cutehmi/xml/ParseElement.cpp \
    src/cutehmi/xml/ParseHelper.cpp \
    src/cutehmi/xml/internal/functions.cpp \
    src/cutehmi/internal/PluginNodeData.cpp \
    src/cutehmi/XMLBackendPlugin.cpp \
    src/cutehmi/internal/macros.cpp \
    src/cutehmi/DataBlock.cpp \
    src/cutehmi/PopupBridge.cpp \
    src/cutehmi/Prompt.cpp \
    src/cutehmi/Notification.cpp \
    src/cutehmi/NotificationManager.cpp \
    src/cutehmi/NotificationListModel.cpp \
    src/cutehmi/ProjectNodeData.cpp \
    src/cutehmi/Worker.cpp \
    src/cutehmi/xml/conversions.cpp

HEADERS += \
    include/cutehmi/ProjectModel.hpp \
    include/cutehmi/Error.hpp \
    include/cutehmi/PluginLoader.hpp \
    include/cutehmi/ErrorInfo.hpp \
    include/cutehmi/Project.hpp \
    include/cutehmi/CuteHMI.hpp \
    include/cutehmi/internal/ProjectXMLBackend.hpp \
    include/cutehmi/Exception.hpp \
    include/cutehmi/ErrorException.hpp \
    include/cutehmi/internal/common.hpp \
    include/cutehmi/internal/platform.hpp \
    include/cutehmi/internal/macros.hpp \
    include/cutehmi/ProjectNode.hpp \
    include/cutehmi/Plugin.hpp \
    include/cutehmi/xml/ParseAttribute.hpp \
    include/cutehmi/xml/ParseElement.hpp \
    include/cutehmi/xml/ParseHelper.hpp \
    include/cutehmi/xml/internal/functions.hpp \
    include/cutehmi/IPlugin.hpp \
    include/cutehmi/IXMLBackendPlugin.hpp \
    include/cutehmi/internal/PluginNodeData.hpp \
    include/cutehmi/XMLBackendPlugin.hpp \
    include/cutehmi/macros.hpp \
    include/cutehmi/DataBlock.hpp \
    include/cutehmi/ExceptionMixin.hpp \
    include/cutehmi/PopupBridge.hpp \
    include/cutehmi/Prompt.hpp \
    include/cutehmi/Notification.hpp \
    include/cutehmi/NotificationManager.hpp \
    include/cutehmi/NotificationListModel.hpp \
    include/cutehmi/ProjectNodeData.hpp \
    include/cutehmi/Worker.hpp \
    include/cutehmi/xml/conversions.hpp

DISTFILES += \
    import.pri \
    libdef.pri \
    dev/cutehmi_1-1.workaround.Qt.design.txt \
    dev/cutehmi_1-2.workaround.std.design.txt

RESOURCES +=
