#ifndef H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_IMETADATAPLUGIN_HPP
#define H_EXTENSIONS_CUTEHMI_2_INCLUDE_CUTEHMI_IMETADATAPLUGIN_HPP

#include "internal/common.hpp"
#include "ProjectNode.hpp"

#include <QtPlugin>

namespace cutehmi {

/**
 * Metadata plugin interface.
 */
class CUTEHMI_API IMetadataPlugin
{
	protected:
		virtual ~IMetadataPlugin() = default; // Making dtor virtual for plugin interface as in Qt docs.

		IMetadataPlugin() = default;
};

}

#define CUTEHMI_IMETADATAPLUGIN_IID "cutehmi::IMetadataPlugin"
Q_DECLARE_INTERFACE(cutehmi::IMetadataPlugin, CUTEHMI_IMETADATAPLUGIN_IID)

#endif

//(c)MP: Copyright © 2019, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
