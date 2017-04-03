#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_CUTEHMI_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_CUTEHMI_HPP

#include "internal/common.hpp"
#include "Project.hpp"

#include <QObject>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API CuteHMI:
	public QObject
{
	Q_OBJECT

	public:
		/**
		 * Get instance. Gets a reference to the instance of the singleton class.
		 * @return a reference to the instance of the singleton class.
		 *
		 * @warning Typically Destroy() function should be used to satisfy the requirement
		 * that QApplication has to be first created and last destroyed QObject.
		 *
		 * @warning if Destroy() function is not used, then destructor will be
		 * called on static de-initialization. Beware of using singleton instance in
		 * destructor of some other static object. If that's unavoidable, assure that
		 * singletons or any static objects are constructed in the reverse order they are
		 * going to be destructed.
		 *
		 * @internal utils::Singleton is not being used to prevent inlining of template
		 * function and incorporating static instance into other translation units.
		 */
		static CuteHMI & Instance();

		/**
		 * Destroy instance. This function is provided to satisfy the requirement that
		 * QApplication has to be first created and last destroyed QObject.
		 * Once this function is called singleton becomes unusable.
		 */
		static void Destroy();

		Project * project() const;

	protected:
		CuteHMI();

		static std::unique_ptr<CuteHMI> & InstancePtr();

	private:
		struct Members
		{
			std::unique_ptr<Project> project;
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
