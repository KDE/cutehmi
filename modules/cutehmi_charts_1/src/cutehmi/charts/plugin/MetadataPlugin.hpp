#ifndef H_MODULES_CUTEHMI__1_SRC_CUTEHMI_CHARTS_PLUGIN_METADATAPLUGIN_HPP
#define H_MODULES_CUTEHMI__1_SRC_CUTEHMI_CHARTS_PLUGIN_METADATAPLUGIN_HPP

#include "../../../../cutehmi.metadata.hpp"

#include <cutehmi/IMetadataPlugin.hpp>

#include <QObject>

namespace cutehmi {
namespace plugin {

class MetadataPlugin:
	public QObject
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID CUTEHMI_IMETADATAPLUGIN_IID FILE "../../../../cutehmi.metadata.json")

	public:
		~MetadataPlugin() override = default;
};

}
}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
