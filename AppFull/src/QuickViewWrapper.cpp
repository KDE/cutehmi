#include "QuickViewWrapper.hpp"

#include <QQmlEngine>
#include <QQuickView>
#include <QWidget>

QuickViewWrapper::QuickViewWrapper(QWidget * parent):
	Parent(new QQmlEngine),
	m_quickView(new QQuickView(engine(), 0)) // Note: QQuickView won't take ownership of m_qmlEngine.
{
	m_quickView->setResizeMode(QQuickView::SizeRootObjectToView);
	engine()->setParent(m_quickView);	// Reparent m_qmlEngine so that proper destruction order is guaranteed.
	m_widget = QWidget::createWindowContainer(m_quickView, parent);	// Note: m_widget (window container) should take ownership of m_quickView.
}

QWidget * QuickViewWrapper::widget() const
{
	return m_widget;
}

QQuickItem * QuickViewWrapper::contentItem() const
{
	return m_quickView->contentItem();
}
