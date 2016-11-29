#ifndef CUTEHMI_LIBBASE_SRC_BASE_PROJECT_HPP
#define CUTEHMI_LIBBASE_SRC_BASE_PROJECT_HPP

#include "../platform.hpp"
#include "PluginLoader.hpp"
#include "ProjectModel.hpp"
#include "Services.hpp"

#include <QQmlEngine>

namespace cutehmi {
namespace base {

/**
 * Project. Encapsulates objects related to a project and provides neat interface to deal with projects.
 *
 * @todo implement.
 */
class CUTEHMI_BASE_API Project
{
	public:
		struct CUTEHMI_BASE_API Error:
			public base::Error
		{
			enum : int {
				FILE_NOT_EXISTS = Error::SUBCLASS_BEGIN,
				FILE_UNABLE_TO_OPEN,
				FILE_EMPTY_NAME
			};

			using base::Error::Error;

			QString str() const;
		};

		Project();

	private:
		//<assumption id="cutehmi.base.Project-projectModel_engine-destructionOrder">
		// It's quite important to destroy "engine" before "projectModel", because ProjectModel contains context properties,
		// which may still be in use by some QML components (for example in "Component.onDestroyed" handlers).
		ProjectModel m_projectModel;
		QQmlEngine m_engine;
		//</assumption>
		Services m_services;
		PluginLoader m_pluginLoader;
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
