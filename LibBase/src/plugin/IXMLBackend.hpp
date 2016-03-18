#ifndef CUTEHMI_LIBBASE_SRC_PLUGIN_IXMLBACKEND_HPP
#define CUTEHMI_LIBBASE_SRC_PLUGIN_IXMLBACKEND_HPP

#include "../platform.hpp"
#include "../base/Error.hpp"
#include "../base/ProjectModel.hpp"

#include <QtPlugin>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace cutehmi {
namespace plugin {

/**
 * @todo gather all PLC plugin interfaces into IPLCPlugin.
 *
 * @todo move it to some different namespace.
 */
class IXMLBackend
{
	public:
		virtual base::Error readXML(QXmlStreamReader & xmlReader, base::ProjectModel::Node & node) = 0;

		virtual base::Error writeXML(QXmlStreamWriter & xmlWriter) const = 0;

	protected:
		virtual ~IXMLBackend() = default;

		IXMLBackend() = default;
};

}
}

Q_DECLARE_INTERFACE(cutehmi::plugin::IXMLBackend, "CuteHMI.Plugin.IXMLBackend")

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
