#ifndef H_MODULES_CUTEHMI__XML__1_INCLUDE_CUTEHMI_XML_IBACKENDPLUGIN_HPP
#define H_MODULES_CUTEHMI__XML__1_INCLUDE_CUTEHMI_XML_IBACKENDPLUGIN_HPP

#include "internal/common.hpp"

#include <cutehmi/ProjectNode.hpp>

#include <QtPlugin>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

namespace cutehmi {
namespace xml {

/**
 * Plugin interface.
 */
class CUTEHMI_XML_API IBackendPlugin
{
	public:
		virtual void readXML(QXmlStreamReader & xmlReader, ProjectNode & node) = 0;

		virtual void writeXML(QXmlStreamWriter & xmlWriter, ProjectNode & node) const noexcept(false) = 0;

	protected:
		virtual ~IBackendPlugin() = default; // Making dtor virtual for plugin interface as in Qt docs.

		IBackendPlugin() = default;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
