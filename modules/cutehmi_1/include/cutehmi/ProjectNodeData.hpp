#ifndef H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_PROJECTNODEDATA_HPP
#define H_MODULES_CUTEHMI_u_1_INCLUDE_CUTEHMI_PROJECTNODEDATA_HPP

#include "internal/common.hpp"
#include "DataBlock.hpp"

namespace cutehmi {

/**
 * %Project node data. This class encapsulates basic data required by each
 * project node. Plugins may attach their own data to the node using DataBlock
 * interface.
 */
class CUTEHMI_API ProjectNodeData final:
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

		MPtr<Members> m;
};

}

#endif

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
