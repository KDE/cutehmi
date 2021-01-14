#include "QMLPlugin.hpp"
#include "qqmlsettings_p.h"

#include <cutehmi/workarounds/qt/labs/settings/metadata.hpp>

#include <QtQml>

//<Doxygen-3.workaround target="Doxygen" cause="missing">
#ifdef DOXYGEN_WORKAROUND

namespace CuteHMI {
namespace Workarounds {
namespace Qt {
namespace labs {
namespace settings {

/**
 * Exposes cutehmi::workarounds::qt::labs::settings::internal::QQmlSettings to QML.
 */
class Settings: public cutehmi::workarounds::qt::labs::settings::internal::QQmlSettings {};

}
}
}
}
}

#endif
//</Doxygen-3.workaround>

namespace cutehmi {
namespace workarounds {
namespace qt {
namespace labs {
namespace settings {
namespace internal {

/**
 * Register QML types.
 * @param uri URI.
 */
void QMLPlugin::registerTypes(const char * uri)
{
	Q_ASSERT(uri == QLatin1String("CuteHMI.Workarounds.Qt.labs.settings"));

	qmlRegisterType<QQmlSettings>(uri, CUTEHMI_WORKAROUNDS_QT_LABS_SETTINGS_MAJOR, 0, "Settings");
}

}
}
}
}
}
}
