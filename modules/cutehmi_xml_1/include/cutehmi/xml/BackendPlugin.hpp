#ifndef H_MODULES_CUTEHMI__XML__1_INCLUDE_CUTEHMI_XML_BACKENDPLUGIN_HPP
#define H_MODULES_CUTEHMI__XML__1_INCLUDE_CUTEHMI_XML_BACKENDPLUGIN_HPP

#include "internal/common.hpp"
#include "IBackendPlugin.hpp"

#include <QObject>

#include <memory>

namespace cutehmi {
namespace xml {

/**
 * Bakcend plugin. Object that wraps IBackendPlugin interface inside QObject.
 * This allows objects implementing IBackendPlugin interface to be registered
 * as extensions with ProjectNode::registerExtension() function. XML loader can
 * recognize these extensions and make use of IBackendPlugin interface to
 * delegate parsing of a portion of XML document to a plugin.
 */
class CUTEHMI_XML_API BackendPlugin:
	public QObject
{
	Q_OBJECT

	public:
		/**
		 * Constructor.
		 * @param implementation object implementing IBackendPlugin interface.
		 * @param parent parent object.
		 */
		explicit BackendPlugin(IBackendPlugin * implementation, QObject * parent = nullptr);

		/**
		 * Get object implementing IBackendPlugin interface.
		 * @return object implementing IBackendPlugin interface.
		 */
		IBackendPlugin * implementation();

	private:
		struct Members
		{
			IBackendPlugin * implementation;
		};

		MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
