#include "../../include/cutehmi/ProjectNode.hpp"

#include <QtDebug>
#include <QQmlContext>
#include <QUuid>
#include <QQmlEngine>

namespace cutehmi {

QObject * ProjectNode::extension(const QString & extensionId) const
{
	return extensions()->value(extensionId, nullptr);
}

void ProjectNode::registerExtension(const QString & extensionId, QObject * extension)
{
	QQmlEngine::setObjectOwnership(extension, QQmlEngine::CppOwnership);
	extensions()->insert(extensionId, extension);
}

void ProjectNode::registerExtension(QObject * extension)
{
    registerExtension(extension->metaObject()->className(), extension);
}

QStringList ProjectNode::extensionIds() const
{
	return extensions()->keys();
}

const ProjectNodeData & ProjectNode::data() const
{
	return m->data;
}

ProjectNodeData & ProjectNode::data()
{
	return m->data;
}

const ProjectNode * ProjectNode::parent() const
{
	return m->parent;
}

ProjectNode * ProjectNode::parent()
{
	return m->parent;
}

const ProjectNode * ProjectNode::root() const
{
	return const_cast<ProjectNode *>(this)->root();
}

ProjectNode * ProjectNode::root()
{
	ProjectNode * result = this;
	while (result->parent() != nullptr)
		result = result->parent();
	return result;
}

QString ProjectNode::id() const
{
	return m->id;
}

ProjectNode * ProjectNode::appendChild(const QString & id, ProjectNodeData && data, bool leaf)
{
	CUTEHMI_ASSERT(child(id) == nullptr, QString("child with specified id '%1' already exists").arg(id).toLocal8Bit().constData());

	ProjectNode * child = leaf ? new ProjectNode(id, std::move(data), nullptr) :
								 new ProjectNode(id, std::move(data), std::unique_ptr<ChildrenContainer>(new ChildrenContainer));
	QQmlEngine::setObjectOwnership(child, QQmlEngine::CppOwnership);
	children()->append(child);
	child->setParent(this, children()->size() - 1);
	return child;
}

ProjectNode * ProjectNode::appendChild(ProjectNodeData && data, bool leaf)
{
    return appendChild(QUuid::createUuid().toString(), std::move(data), leaf);
}

const ProjectNode * ProjectNode::child(int index) const
{
	if (isLeaf())
		return nullptr;
	return children()->value(index, nullptr);
}

ProjectNode * ProjectNode::child(int index)
{
	return const_cast<ProjectNode *>(const_cast<const ProjectNode *>(this)->child(index));
}

const ProjectNode * ProjectNode::child(const QString & id) const
{
	if (isLeaf())
		return nullptr;
	for (ChildrenContainer::const_iterator it = children()->begin(); it != children()->end(); ++it)
		if ((*it)->id() == id)
			return *it;
	return nullptr;
}

ProjectNode * ProjectNode::child(const QString & id)
{
	return const_cast<ProjectNode *>(const_cast<const ProjectNode *>(this)->child(id));
}

int ProjectNode::childIndex(const ProjectNode * child) const
{
	if (child->parent() != this)
		return -1;
	return child->index();
}

QStringList ProjectNode::childIds() const
{
	QStringList result;
	if (isLeaf())
		return result;
	for (ChildrenContainer::const_iterator it = children()->begin(); it != children()->end(); ++it)
		result << (*it)->id();
	return result;
}

int ProjectNode::countChildren() const
{
	if (isLeaf())
		return 0;
	return children()->count();
}

bool ProjectNode::invoke(const QString & extensionId, const char * method, QGenericReturnArgument returnValue, QGenericArgument val0, QGenericArgument val1, QGenericArgument val2, QGenericArgument val3,	QGenericArgument val4, QGenericArgument val5, QGenericArgument val6, QGenericArgument val7,	QGenericArgument val8, QGenericArgument val9)
{
	CUTEHMI_ASSERT(extension(extensionId), QString("extension '%1' not found").arg(extensionId).toLocal8Bit().constData());

	return QMetaObject::invokeMethod(extension(extensionId), method, returnValue, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9);
}

bool ProjectNode::invoke(const QString & extensionId, const char * method, QGenericArgument val0, QGenericArgument val1, QGenericArgument val2, QGenericArgument val3,	QGenericArgument val4, QGenericArgument val5, QGenericArgument val6, QGenericArgument val7,	QGenericArgument val8, QGenericArgument val9)
{
	CUTEHMI_ASSERT(extension(extensionId), QString("extension '%1' not found").arg(extensionId).toLocal8Bit().constData());

	return QMetaObject::invokeMethod(extension(extensionId), method, val0, val1, val2, val3, val4, val5, val6, val7, val8, val9);
}

ProjectNode::ProjectNode(const QString & id, ProjectNodeData && data, std::unique_ptr<ChildrenContainer> children):
	m(new Members{
	  nullptr,
	  0,
	  id,
	  std::move(data),
	  nullptr,
	  std::move(children)})
{
}

int ProjectNode::index() const
{
	return m->index;
}

void ProjectNode::setParent(ProjectNode * parent, int index)
{
	m->parent = parent;
	m->index = index;
}

bool ProjectNode::isLeaf() const
{
	return m->children == nullptr;
}

const ProjectNode::ExtensionsContainer * ProjectNode::extensions() const
{
	if (m->extensions == nullptr)
		const_cast<ProjectNode *>(this)->allocateExtensions();
	return m->extensions.get();
}

ProjectNode::ExtensionsContainer * ProjectNode::extensions()
{
	return const_cast<ExtensionsContainer *>(const_cast<const ProjectNode *>(this)->extensions());
}


const ProjectNode::ChildrenContainer * ProjectNode::children() const
{
	if (m->children == nullptr) {
		CUTEHMI_LOG_WARNING("Implicitly promoting leaf " << data().name() << " to a child.");
		const_cast<ProjectNode *>(this)->allocateChildren();
	}
	return m->children.get();
}

ProjectNode::ChildrenContainer * ProjectNode::children()
{
	return const_cast<ChildrenContainer *>(const_cast<const ProjectNode *>(this)->children());
}

ProjectNode::~ProjectNode()
{
	if (m->children != nullptr)
		while (!m->children->isEmpty())
			delete m->children->takeLast();
}

void ProjectNode::allocateExtensions()
{
	m->extensions.reset(new ExtensionsContainer);
}

void ProjectNode::allocateChildren()
{
	m->children.reset(new ChildrenContainer);
}

}

//(c)MP: Copyright © 2018, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
