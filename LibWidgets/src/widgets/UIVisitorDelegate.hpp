#ifndef CUTEHMI_LIBWIDGETS_SRC_WIDGETS_UIVISITORDELEGATE_HPP
#define CUTEHMI_LIBWIDGETS_SRC_WIDGETS_UIVISITORDELEGATE_HPP

#include "../platform.hpp"

#include <QMenu>

#include <memory>

namespace cutehmi {
namespace widgets {

/**
 * UI visitor delegate.
 */
class CUTEHMI_WIDGETS_API UIVisitorDelegate
{
	public:
		/**
		 * Context menu proxy. This is used to customize context menu in the visited object.
		 */
		class CUTEHMI_WIDGETS_API ContextMenuProxy
		{
			public:
				/**
				 * Constructor.
				 * @param menu reference to a menu pointer. Pointer should probably point to @p nullptr as
				 * visiting object may reset it.
				 */
				ContextMenuProxy(std::unique_ptr<QMenu> & menu);

				/**
				 * Pass the menu from the caller to the visited object.
				 * @param menu menu to be passed.
				 */
				void pass(std::unique_ptr<QMenu> menu);

			private:
				std::unique_ptr<QMenu> & m_menu;
		};

		virtual ~UIVisitorDelegate() = default;

		/**
		 * Visit context menu proxy. Default implementation does nothing.
		 * @param proxy context menu proxy.
		 */
		virtual void visit(ContextMenuProxy & proxy);
};

}
}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
