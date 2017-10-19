#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_PROJECTNODEDATA_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_PROJECTNODEDATA_HPP

#include "internal/common.hpp"
#include "DataBlock.hpp"

#include <utils/MPtr.hpp>

namespace cutehmi {
namespace base {

/**
 * Project node data. This class encapsulates basic data required by each project node. Plugins may attach their
 * own data to the node using DataBlock interface.
 */
class CUTEHMI_BASE_API ProjectNodeData final:
	public DataBlock
{
	public:
		/**
		 * Constructor.
		 * @param name name of the item. It will be used to display item in the view.
		 */
		explicit ProjectNodeData(const QString & name);

		ProjectNodeData(ProjectNodeData && other) = default;

		ProjectNodeData & operator =(ProjectNodeData && other) = default;

		/**
		 * Get name.
		 * @return name.
		 */
		QString name() const;

		/**
		 * Set name.
		 * @param name node name.
		 */
		void setName(const QString & name);

	private:
		struct Members
		{
			QString name;
			//QIcon icon;
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
