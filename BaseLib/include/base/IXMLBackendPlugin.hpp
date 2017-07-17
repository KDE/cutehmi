#ifndef CUTEHMI_BASELIB_INCLUDE_BASE_IXMLBACKENDPLUGIN_HPP
#define CUTEHMI_BASELIB_INCLUDE_BASE_IXMLBACKENDPLUGIN_HPP

#include "internal/common.hpp"
#include "ProjectNode.hpp"

#include <QtPlugin>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace cutehmi {
namespace base {

/**
 * Plugin interface.
 */
class IXMLBackendPlugin
{
	public:
		virtual void readXML(QXmlStreamReader & xmlReader, ProjectNode & node) = 0;

		virtual void writeXML(QXmlStreamWriter & xmlWriter, ProjectNode & node) const = 0;

	protected:
		virtual ~IXMLBackendPlugin() = default; // Making dtor virtual for plugin interface as in Qt docs.

		IXMLBackendPlugin() = default;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
