#ifndef H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_CUTEHMI_HPP
#define H_MODULES_CUTEHMI__1_INCLUDE_CUTEHMI_CUTEHMI_HPP

#include "internal/common.hpp"
#include "Project.hpp"
#include "PopupBridge.hpp"
#include "NotificationManager.hpp"

#include <QObject>

namespace cutehmi {

/**
 * %CuteHMI singleton. This is a cornerstone object, which acts as a bridge between various parts of the framework.
 * It exposes essential properties to frontend applications, plugins and QML components.
 *
 * To retrieve singleton use Instance() function. Frontend applications may need to call Destroy() function to
 * satisfy destruction order requirements.
 */
class CUTEHMI_API CuteHMI:
	public QObject
{
	Q_OBJECT

	public:
		Q_PROPERTY(Project * project READ project CONSTANT)	///< %Project. This property is never @p nullptr, unless CuteHMI singleton is destroyed.
		Q_PROPERTY(PopupBridge * popupBridge READ popupBridge CONSTANT)	///< %Popup bridge. This property is never @p nullptr, unless CuteHMI singleton is destroyed.
		Q_PROPERTY(NotificationManager * notificationManager READ notificationManager CONSTANT) ///< %Notification manager. This property is never @p nullptr, unless CuteHMI singleton is destroyed.

		/**
		 * Get instance. Gets a reference to the instance of the singleton class.
		 * Calling this function for the first time will also result in registering
		 * some types with qRegisterMetaType() function. Types that are registered:
		 *	- cutehmi::ErrorInfo
		 *  - cutehmi::Prompt::button_t
		 *	- const cutehmi::ProjectNode *
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
		 *
		 * @note only frontend applications, which instantiate QApplication should take care about
		 * this function.
		 */
		static void Destroy();

		/**
		 * Get project.
		 * @return project.
		 */
		Project * project() const;

		/**
		 * Get popup bridge.
		 * @return popup bridge.
		 */
		PopupBridge * popupBridge() const;

		/**
		 * Get notification manager.
		 * @return notification manager.
		 */
		NotificationManager * notificationManager() const;

	protected:
		/**
		 * Default constructor.
		 */
		CuteHMI();

		/**
		 * Get instance pointer.
		 * @return instance pointer.
		 *
		 * @note this is provided as a workaround (id="cutehmi_1-2").
		 */
		static std::unique_ptr<CuteHMI> & InstancePtr();

	private:
		struct Members
		{
			std::unique_ptr<PopupBridge> popupBridge;
			std::unique_ptr<NotificationManager> notificationManager;
			std::unique_ptr<Project> project;
		};

		MPtr<Members> m;
};

}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
