#ifndef CUTEHMI_WORKAROUNDS_QT5COMPATIBILITY_QSIZETYPE_HPP
#define CUTEHMI_WORKAROUNDS_QT5COMPATIBILITY_QSIZETYPE_HPP

//<CuteHMI.Workarounds.Qt5Compatibility-1.workaround target="Qt" cause="Qt5">

#include <QtGlobal>

namespace cutehmi {
namespace workarounds {
namespace qt5compatibility {

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
typedef qsizetype sizeType;
#else
typedef int sizeType;
#endif

}
}
}

//</CuteHMI.Workarounds.Qt5Compatibility-1.workaround>

#endif
