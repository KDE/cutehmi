#include "../../include/base/ProjectNode.hpp"

#include <QtDebug>
#include <QQmlContext>
#include <QUuid>

namespace cutehmi {
namespace base {

ProjectNode::Data::Data(const QString & name):
	m_name(name)
{
}

QString ProjectNode::Data::name() const
{
	return m_name;
}

void ProjectNode::Data::setName(const QString & name)
{
	m_name = name;
}

QObject * ProjectNode::extension(const QString & extensionId)
{
	return extensions()->value(extensionId, nullptr);
}

void ProjectNode::addExtension(const QString & extensionId, QObject * extension)
{
	extensions()->insert(extensionId, extension);
}

void ProjectNode::addExtension(QObject * extension)
{
	addExtension(extension->metaObject()->className(), extension);
}

QStringList ProjectNode::extensionIds() const
{
	return extensions()->keys();
}

const ProjectNode::Data & ProjectNode::data() const
{
	return m->data;
}

ProjectNode::Data & ProjectNode::data()
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

ProjectNode * ProjectNode::addChild(const QString & id, Data && data, bool leaf)
{
	CUTEHMI_BASE_ASSERT(child(id) == nullptr, "Child with specified id (" << id << ") already exists.");

	ProjectNode * child = leaf ? new ProjectNode(id, std::move(data), nullptr) :
										new ProjectNode(id, std::move(data), std::unique_ptr<ChildrenContainer>(new ChildrenContainer));
	children()->append(child);
	child->setParent(this, children()->size() - 1);
	return child;
}

ProjectNode * ProjectNode::addChild(Data && data, bool leaf)
{
	return addChild(QUuid::createUuid().toString(), std::move(data), leaf);
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

ProjectNode::ProjectNode(const QString & id, Data && data, std::unique_ptr<ChildrenContainer> children):
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
		CUTEHMI_BASE_QWARNING("Implicitly promoting leaf " << data().name() << " to a child.");
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
}
