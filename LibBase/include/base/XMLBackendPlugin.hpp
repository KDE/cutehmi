#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_XMLBACKENDPLUGIN_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_XMLBACKENDPLUGIN_HPP

#include "internal/common.hpp"
#include "IXMLBackendPlugin.hpp"

#include <QObject>

#include <memory>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API XMLBackendPlugin:
	public QObject
{
	Q_OBJECT

	public:
		explicit XMLBackendPlugin(IXMLBackendPlugin * implementation, QObject * parent = 0);

		IXMLBackendPlugin * implementation();

	private:
		struct Members
		{
			IXMLBackendPlugin * implementation;
		};

		std::unique_ptr<Members> m;
};

}
}

#endif
