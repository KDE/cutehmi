#include "QuickWidgetWrapper.hpp"

#include <QQuickWidget>
#include <QQmlEngine>

namespace cutehmi {
namespace widgets {

QuickWidgetWrapper::QuickWidgetWrapper(QWidget * parent):
	Parent(new QQmlEngine),
	m_quickWidget(new QQuickWidget(engine(), parent)) // Note: QQuickWidget won't take ownership of m_qmlEngine.
{
	m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
	engine()->setParent(m_quickWidget);	// Reparent m_qmlEngine so that proper destruction order is guaranteed.
}

QWidget * QuickWidgetWrapper::widget() const
{
	return m_quickWidget;
}

QQuickItem * QuickWidgetWrapper::contentItem() const
{
	return m_quickWidget->quickWindow()->contentItem();
}

}
}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
