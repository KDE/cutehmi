#ifndef CUTEHMI_LIBBASE_SRC_BASE_IPLCPLUGIN_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_IPLCPLUGIN_HPP

#include "../platform.hpp"
#include "Error.hpp"
#include "ProjectModel.hpp"

#include <QtPlugin>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace cutehmi {
namespace base {

/**
 * PLC client plugin interface.
 */
class IPLCPlugin
{
	public:
		virtual base::Error readXML(QXmlStreamReader & xmlReader, ProjectModel::Node & node) = 0;

		virtual base::Error writeXML(QXmlStreamWriter & xmlWriter) const = 0;

	protected:
		virtual ~IPLCPlugin() = default; // Making dtor virtual for plugin interface as in Qt docs.

		IPLCPlugin() = default;
};

}
}

Q_DECLARE_INTERFACE(cutehmi::base::IPLCPlugin, "CuteHMI.Base.IPLCPlugin")

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
