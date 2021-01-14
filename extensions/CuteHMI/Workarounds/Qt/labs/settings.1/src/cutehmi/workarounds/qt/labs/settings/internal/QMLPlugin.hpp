#ifndef H_EXTENSIONS_CUTEHMI_WORKAROUNDS_QMLPLUGIN_HPP
#define H_EXTENSIONS_CUTEHMI_WORKAROUNDS_QMLPLUGIN_HPP

#include <QQmlExtensionPlugin>

class QJSEngine;

namespace cutehmi {
namespace workarounds {
namespace qt {
namespace labs {
namespace settings {
namespace internal {

class QMLPlugin:
	public QQmlExtensionPlugin
{
		Q_OBJECT
		Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

	public:
		void registerTypes(const char * uri) override;
};

}
}
}
}
}
}

#endif

