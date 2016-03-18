#ifndef CUTEHMI_APPFULL_SRC_QUICKWIDGETWRAPPER_HPP
#define CUTEHMI_APPFULL_SRC_QUICKWIDGETWRAPPER_HPP

#include "AbstractQMLWidgetWrapper.hpp"

class QQuickWidget;

namespace cutehmi {

/**
 * QQuickWidget wrapper. Provides QQuickWidget based rendering for QML.
 */
class QuickWidgetWrapper:
	public AbstractQMLWidgetWrapper
{
	typedef AbstractQMLWidgetWrapper Parent;

	public:
		QuickWidgetWrapper(QWidget * parent);

		QWidget * widget() const override;

		QQuickItem * contentItem() const override;

	private:
		QQuickWidget * m_quickWidget;
};

}

#endif

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
