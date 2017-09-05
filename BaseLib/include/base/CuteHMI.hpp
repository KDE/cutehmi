#ifndef CUTEHMI_BASELIB_INCLUDE_BASE_CUTEHMI_HPP
#define CUTEHMI_BASELIB_INCLUDE_BASE_CUTEHMI_HPP

#include "internal/common.hpp"
#include "Project.hpp"
#include "PopupBridge.hpp"
#include "NotificationManager.hpp"

#include <QObject>

namespace cutehmi {
namespace base {

class CUTEHMI_BASE_API CuteHMI:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(Project * project READ project NOTIFY projectChanged)
		Q_PROPERTY(PopupBridge * popupBridge READ popupBridge NOTIFY popupBridgeChanged)
		Q_PROPERTY(NotificationManager * notificationManager READ notificationManager NOTIFY notificationManagerChanged)

		/**
		 * Get instance. Gets a reference to the instance of the singleton class.
		 * Calling this function for the first time will also result in registering
		 * some types with qRegisterMetaType() function. Types that are registered:
		 *	- cutehmi::base::ErrorInfo
		 *  - cutehmi::base::Prompt::button_t
		 *	- const cutehmi::base::ProjectNode *
		 *  .
		 *
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

		PopupBridge * popupBridge() const;

		NotificationManager * notificationManager() const;

	signals:
		void projectChanged();

		void popupBridgeChanged();

		void notificationManagerChanged();

	protected:
		CuteHMI();

		static std::unique_ptr<CuteHMI> & InstancePtr();

	private:
		struct Members
		{
			std::unique_ptr<PopupBridge> popupBridge;
			std::unique_ptr<NotificationManager> notificationManager;
			std::unique_ptr<Project> project;
		};

		utils::MPtr<Members> m;
};

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
