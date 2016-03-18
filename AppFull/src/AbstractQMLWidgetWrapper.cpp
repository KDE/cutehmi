#include "AbstractQMLWidgetWrapper.hpp"

#include <QQmlComponent>
#include <QtDebug>
#include <QQmlEngine>
#include <QQuickItem>
#include <QQmlContext>

namespace cutehmi {

QQmlContext * AbstractQMLWidgetWrapper::rootContext() const
{
	return engine()->rootContext();
}

void AbstractQMLWidgetWrapper::setSource(const QUrl & url)
{
	qDebug() << "Loading QML file: " << url;

	m_protoVisualComponent->loadUrl(url);
	if (m_protoVisualComponent->isLoading())
		connect(m_protoVisualComponent, & QQmlComponent::statusChanged, this, & AbstractQMLWidgetWrapper::showVisualComponent);
	else
		showVisualComponent();
}

QQmlContext * AbstractQMLWidgetWrapper::projectContext() const
{
	return m_projectContext;
}

QQmlComponent * AbstractQMLWidgetWrapper::protoVisualComponent() const
{
	return m_protoVisualComponent;
}

QStringList AbstractQMLWidgetWrapper::importPathList() const
{
	return m_qmlEngine->importPathList();
}

void AbstractQMLWidgetWrapper::addImportPath(const QString & dir)
{
	qDebug() << "Adding QML import path: " << dir;
	m_qmlEngine->addImportPath(dir);
}

void AbstractQMLWidgetWrapper::resetVisualComponent(QQuickItem * component)
{
	if (m_visualComponent) {
		m_visualComponent->setParentItem(nullptr);
		delete m_visualComponent;
	}
	m_visualComponent = component;
}

void AbstractQMLWidgetWrapper::renewProjectContext()
{
	delete m_projectContext;
	m_projectContext = new QQmlContext(engine()->rootContext());
}

void AbstractQMLWidgetWrapper::showVisualComponent()
{
	if (m_protoVisualComponent->isNull())
		return;
	if (m_protoVisualComponent->isError())
		qWarning() << m_protoVisualComponent->errors();
	else {
		QQuickItem * visualComponent = qobject_cast<QQuickItem *>(m_protoVisualComponent->create(m_projectContext));
		if (visualComponent == nullptr)
			qWarning() << "Failed to cast component to QQuickItem.";
		else {
			resetVisualComponent(visualComponent);
			m_visualComponent->setParentItem(contentItem());	// Show the new visual component.
		}
	}
	renewProtoVisualComponent();
}

AbstractQMLWidgetWrapper::AbstractQMLWidgetWrapper(QQmlEngine * qmlEngine):
	m_qmlEngine(qmlEngine),
	m_protoVisualComponent(new QQmlComponent(qmlEngine)),
	m_visualComponent(nullptr),
	m_projectContext(new QQmlContext(qmlEngine->rootContext()))
{
}

AbstractQMLWidgetWrapper::~AbstractQMLWidgetWrapper()
{
	if (m_visualComponent) {
		m_visualComponent->setParentItem(nullptr);
		delete m_visualComponent;
	}
	delete m_projectContext;
	delete m_protoVisualComponent;
}

QQmlEngine * AbstractQMLWidgetWrapper::engine() const
{
	return m_qmlEngine;
}

void AbstractQMLWidgetWrapper::renewProtoVisualComponent()
{
	delete m_protoVisualComponent;
	m_protoVisualComponent = new QQmlComponent(engine());
}

}

//(c)MP: Copyright © 2016, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
