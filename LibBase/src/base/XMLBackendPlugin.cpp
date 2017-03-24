#include "../../include/base/XMLBackendPlugin.hpp"

namespace cutehmi {
namespace base {

XMLBackendPlugin::XMLBackendPlugin(IXMLBackendPlugin * implementation, QObject * parent):
	QObject(parent),
	m(new Members{implementation})
{
}

IXMLBackendPlugin * XMLBackendPlugin::implementation()
{
	return m->implementation;
}

}
}
