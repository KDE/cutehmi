#include "QuickWidgetWrapper.hpp"

#include <QQuickWidget>
#include <QQmlEngine>

namespace cutehmi {

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
