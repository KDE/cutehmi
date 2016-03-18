#ifndef CUTEHMI_LIBWIDGETS_SRC_WIDGETS_IUIPLUGIN_HPP
#define CUTEHMI_LIBWIDGETS_SRC_WIDGETS_IUIPLUGIN_HPP

#include <base/IProjectModelVisitor.hpp>

#include <QtPlugin>

namespace cutehmi {
namespace widgets {

/**
 * User-interface plugin interface.
 */
class IUIPlugin:
	public base::IProjectModelVisitor
{
	public:
		/**
		 * Set parent widget. This function may be particulary useful for dialogs and all sorts of windows.
		 *
		 * @param parent parent widget.
		 *
		 * @warning setting a parent in Qt is an equivalent of passing ownership. It may be cumbersome to deal
		 * with plugin widgets with external parent in terms of memory management. Widgets should be destroyed
		 * if plugin objects are no longer in use (for example when project has been closed). One solution is
		 * to connect @a widget's destroyLater() slot with a destroyed() signal of some QObject owned by a delegate.
		 *
		 * @internal It's better to pass parent widget upon widget creation. Qt does weird things if for example
		 * QDialog parent is set using setParent() function.
		 */
		virtual void setParentWidget(QWidget * parent) = 0;

	protected:
		virtual ~IUIPlugin() = default;

		IUIPlugin() = default;
};

}
}

Q_DECLARE_INTERFACE(cutehmi::widgets::IUIPlugin, "CuteHMI.Widgets.IUIPlugin")


#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
