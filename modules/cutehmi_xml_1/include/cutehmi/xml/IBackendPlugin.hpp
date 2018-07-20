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
		/**
		 * Read XML.
		 * @param xmlReader an XML reader instance that should be used to read
		 * relevant portion of XML document.
		 * @param node plugin node. This is the same node as in
		 * IProjectPlugin::init() function. It can be used to register
		 * extensions, put some data into it or append child nodes.
		 */
		virtual void readXML(QXmlStreamReader & xmlReader, ProjectNode & node) = 0;

		/**
		 * Write XML.
		 * @param xmlReader an XML writer instance that should be used to write
		 * relevant portion of XML document.
		 * @param node plugin node.
		 */
		virtual void writeXML(QXmlStreamWriter & xmlWriter, ProjectNode & node) const noexcept(false) = 0;

	protected:
		virtual ~IBackendPlugin() = default; // Making dtor virtual for plugin interface as in Qt docs.

		IBackendPlugin() = default;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
