#include "ProjectModel.hpp"
#include "RunnersRegister.hpp"

#include <QtDebug>
#include <QQmlContext>

namespace cutehmi {
namespace base {

ProjectModel::Node::VisitorDelegate::RunnersRegisterProxy::RunnersRegisterProxy(RunnersRegister * runners):
	m_runners(runners)
{
}

void ProjectModel::Node::VisitorDelegate::RunnersRegisterProxy::add(IRunner * runner)
{
	m_runners->add(runner);
}

ProjectModel::Node::VisitorDelegate::QMLContextPropertyProxy::QMLContextPropertyProxy(QQmlContext * context):
	m_context(context)
{
}

void ProjectModel::Node::VisitorDelegate::QMLContextPropertyProxy::setContextProperty(const QString & name, QObject * value)
{
	if (m_context->contextProperty(name).isValid())
		qWarning() << "Context property" << name << "has been already set.";
	m_context->setContextProperty(name, value);
}

ProjectModel::Node::VisitorDelegate::QMLVisualComponentProxy::QMLVisualComponentProxy(QQmlComponent * component):
	m_component(component)
{
}

void ProjectModel::Node::VisitorDelegate::QMLVisualComponentProxy::loadUrl(const QUrl & url)
{
	m_component->loadUrl(url);
}

void ProjectModel::Node::VisitorDelegate::QMLVisualComponentProxy::loadUrl(const QUrl & url, QQmlComponent::CompilationMode mode)
{
	m_component->loadUrl(url, mode);
}

void ProjectModel::Node::VisitorDelegate::QMLVisualComponentProxy::setData(const QByteArray & data, const QUrl & url)
{
	m_component->setData(data, url);
}

void ProjectModel::Node::VisitorDelegate::visit(RunnersRegisterProxy & proxy)
{
	Q_UNUSED(proxy);
}

void ProjectModel::Node::VisitorDelegate::visit(QMLContextPropertyProxy & proxy)
{
	Q_UNUSED(proxy);
}

void ProjectModel::Node::VisitorDelegate::visit(QMLVisualComponentProxy & proxy)
{
	Q_UNUSED(proxy);
}

widgets::UIVisitorDelegate * ProjectModel::Node::VisitorDelegate::ui()
{
	return nullptr;
}

ProjectModel::Node::Data::Data(const QString & name, std::unique_ptr<QObject> object):
	m_name(name),
	m_object(std::move(object))
{
	if (m_object != nullptr)
		m_object->setParent(0);
}

ProjectModel::Node::Data::Data(Data && other) noexcept:
	m_name(std::move(other.m_name)),
	m_object(std::move(other.m_object))
{
}

ProjectModel::Node::Data::~Data()
{
}

ProjectModel::Node::Data & ProjectModel::Node::Data::operator =(ProjectModel::Node::Data && other) noexcept
{
	// Handle self-assignment.
	if (this == & other)
		return *this;

	m_object = std::move(other.m_object);
	m_name = std::move(other.m_name);
	return *this;
}

void ProjectModel::Node::Data::setObject(std::unique_ptr<QObject> object)
{
	m_object = std::move(object);
	if (m_object != nullptr)
		m_object->setParent(0);
}

QObject * ProjectModel::Node::Data::object() const
{
	return m_object.get();
}

QString ProjectModel::Node::Data::name() const
{
	return m_name;
}

void ProjectModel::Node::Data::setName(const QString & name)
{
	m_name = name;
}

const ProjectModel::Node::Data & ProjectModel::Node::data() const
{
	return m_data;
}

ProjectModel::Node::Data & ProjectModel::Node::data()
{
	return m_data;
}

const ProjectModel::Node * ProjectModel::Node::parent() const
{
	return m_parent;
}

ProjectModel::Node * ProjectModel::Node::parent()
{
	return m_parent;
}

void ProjectModel::Node::setVisitorDelegate(std::unique_ptr<VisitorDelegate> delegate)
{
	m_visitorDelegate = std::move(delegate);
}

const ProjectModel::Node::VisitorDelegate * ProjectModel::Node::visitorDelegate() const
{
	return m_visitorDelegate.get();
}

ProjectModel::Node::VisitorDelegate * ProjectModel::Node::visitorDelegate()
{
	return m_visitorDelegate.get();
}

ProjectModel::Node * ProjectModel::Node::addChild(Data && data, bool leaf)
{
	ProjectModel::Node * child = leaf ? new ProjectModel::Node(std::move(data), nullptr) : new ProjectModel::Node(std::move(data), std::unique_ptr<ChildrenContainer>(new ChildrenContainer));
	children()->append(child);
	child->setParent(this);
	return child;
}

const ProjectModel::Node * ProjectModel::Node::child(int index) const
{
	if (isLeaf())
		return nullptr;
	return children()->value(index, nullptr);
}

ProjectModel::Node * ProjectModel::Node::child(int index)
{
	return const_cast<Node *>(const_cast<const Node *>(this)->child(index));
}

int ProjectModel::Node::childIndex(const Node * child) const
{
	if (isLeaf())
		return -1;
	return children()->indexOf(const_cast<Node *>(child));
}

int ProjectModel::Node::countChildren() const
{
	if (isLeaf())
		return 0;
	return children()->count();
}

ProjectModel::Node::Node(Data && data, std::unique_ptr<ChildrenContainer> children):
	m_parent(nullptr),
	m_data(std::move(data)),
	m_visitorDelegate(new VisitorDelegate),
	m_children(std::move(children))
{
}

void ProjectModel::Node::setParent(Node * parent)
{
	m_parent = parent;
}

bool ProjectModel::Node::isLeaf() const
{
	return m_children == nullptr;
}

const ProjectModel::Node::ChildrenContainer * ProjectModel::Node::children() const
{
	if (m_children == nullptr) {
		qWarning() << "Implicitly promoting leaf " << data().name() << " to a child.";
		const_cast<Node *>(this)->allocateChildren();
	}
	return m_children.get();
}

ProjectModel::Node::ChildrenContainer * ProjectModel::Node::children()
{
	return const_cast<ChildrenContainer *>(const_cast<const Node *>(this)->children());
}

ProjectModel::Node::~Node()
{
	if (m_children != nullptr)
		while (!m_children->isEmpty())
			delete m_children->takeFirst();
}

void ProjectModel::Node::allocateChildren()
{
	m_children.reset(new ChildrenContainer);
}


ProjectModel::ProjectModel(QObject * parent):
	QAbstractItemModel(parent),
	m_root(Node::Data("Root node"), std::unique_ptr<Node::ChildrenContainer>(new Node::ChildrenContainer))
{
}

QModelIndex ProjectModel::index(int row, int column, const QModelIndex & parent) const
{
	// Return immediately invalid index if column is not 0.
	if (column != 0)
		return QModelIndex();

	Node * parentNode;
	// No parent. Use root node.
	if (parent == QModelIndex())
		//<workaround id="LibBase-1" target="Qt" cause="design">
		parentNode = const_cast<Node *>(& m_root);
		//</workaround>
	else
		parentNode = static_cast<Node *>(parent.internalPointer());

	Node * child = parentNode->child(row);
	if (child != nullptr)
		return createIndex(row, column, child);

	// If child does not exist return invalid index.
	return QModelIndex();
}

QModelIndex ProjectModel::parent(const QModelIndex & child) const
{
	if (child == QModelIndex())
		return QModelIndex();

	Node * parentNode = static_cast<Node *>(child.internalPointer())->parent();
	if (parentNode != nullptr) {
		Node * grandParentNode = parentNode->parent();
		if (grandParentNode == nullptr)
			return QModelIndex();	// Root node.
		return createIndex(grandParentNode->childIndex(parentNode), 0, parentNode);
	}
	return QModelIndex();
}

int ProjectModel::rowCount(const QModelIndex & parent) const
{
	if (parent == QModelIndex())
		return m_root.countChildren();
	return static_cast<Node *>(parent.internalPointer())->countChildren();
}

int ProjectModel::columnCount(const QModelIndex & parent) const
{
	Q_UNUSED(parent);

	return 1;
}

QVariant ProjectModel::data(const QModelIndex & index, int role) const
{
	switch (role) {
		//General purpose roles:
		case Qt::DisplayRole:		// "[0] The key data to be rendered in the form of text. (QString)"
			return static_cast<Node *>(index.internalPointer())->data().name();
		case Qt::DecorationRole:	// "[1] The data to be rendered as a decoration in the form of an icon. (QColor, QIcon or QPixmap)"
			return QVariant();	// This should be provided by extended GUI model.
		case Qt::EditRole:			// "[2] The data in a form suitable for editing in an editor. (QString)"
			return QVariant();	// Not applicable.
//		case Qt::ToolTipRole:		// "[3] The data displayed in the item's tooltip. (QString)"
//			return QVariant();	// Currently no tooltip.
//		case Qt::StatusTipRole:		// "[4] The data displayed in the status bar. (QString)"
//			return QVariant(); // Nothing on status bar.
//		case Qt::WhatsThisRole:		// "[5] The data displayed for the item in "What's This?" mode. (QString)"
//			return QVariant(); // Nothing on what's this.
		case Qt::SizeHintRole:		// "[13] The size hint for the item that will be supplied to views. (QSize)"
			return QVariant(); // No size hint.

		// Appearance and metadata roles:
		case Qt::FontRole:				// "[6] The font used for items rendered with the default delegate. (QFont)"
			return QVariant();	// Use standard font.
		case Qt::TextAlignmentRole:		// "[7] The alignment of the text for items rendered with the default delegate. (Qt::AlignmentFlag)"
			return QVariant();	// Standard text alignment.
		case Qt::BackgroundRole:		// "[8] The background brush used for items rendered with the default delegate. (QBrush)"
			return QVariant();	// No special background.
		case Qt::ForegroundRole:		// "[9] The foreground brush (text color, typically) used for items rendered with the default delegate. (QBrush)"
			return QVariant();	// No special foreground.
		case Qt::CheckStateRole:		// "[10] This role is used to obtain the checked state of an item. (Qt::CheckState)"
			return QVariant();	// Item not checkable.
		case Qt::InitialSortOrderRole:	// "[14] This role is used to obtain the initial sort order of a header view section. (Qt::SortOrder). This role was introduced in Qt 4.8"
			return QVariant();	// Use default sort order.

		// Accessibility roles:
		case Qt::AccessibleTextRole:		// "[11] The text to be used by accessibility extensions and plugins, such as screen readers. (QString)"
			return static_cast<Node *>(index.internalPointer())->data().name();
//		case Qt::AccessibleDescriptionRole:	// "[12] A description of the item for accessibility purposes. (QString)"
//			return QVariant();	// No description.

		default:
			qDebug() << "Data item role (" << role << ") not supported yet.";
	}
	return QVariant();
}

QVariant ProjectModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	// Currently only horizontal headers are supported.
	if (orientation != Qt::Horizontal)
		return QVariant();

	// Currently only single column is used.
	if (section != 0)
		return QVariant();

	switch (role) {
		//General purpose roles:
		case Qt::DisplayRole:		// "[0] The key data to be rendered in the form of text. (QString)"
			return m_root.data().name();
		case Qt::DecorationRole:	// "[1] The data to be rendered as a decoration in the form of an icon. (QColor, QIcon or QPixmap)"
			return QVariant();	// This should be provided by extended GUI model.
		case Qt::EditRole:			// "[2] The data in a form suitable for editing in an editor. (QString)"
			return QVariant();	// Not applicable.
//		case Qt::ToolTipRole:		// "[3] The data displayed in the item's tooltip. (QString)"
//			return QVariant();	// Currently no tooltip.
//		case Qt::StatusTipRole:		// "[4] The data displayed in the status bar. (QString)"
//			return QVariant(); // Nothing on status bar.
//		case Qt::WhatsThisRole:		// "[5] The data displayed for the item in "What's This?" mode. (QString)"
//			return QVariant(); // Nothing on what's this.
		case Qt::SizeHintRole:		// "[13] The size hint for the item that will be supplied to views. (QSize)"
			return QVariant(); // No size hint.

		// Appearance and metadata roles:
		case Qt::FontRole:				// "[6] The font used for items rendered with the default delegate. (QFont)"
			return QVariant();	// Use standard font.
		case Qt::TextAlignmentRole:		// "[7] The alignment of the text for items rendered with the default delegate. (Qt::AlignmentFlag)"
			return QVariant();	// Standard text alignment.
		case Qt::BackgroundRole:		// "[8] The background brush used for items rendered with the default delegate. (QBrush)"
			return QVariant();	// No special background.
		case Qt::ForegroundRole:		// "[9] The foreground brush (text color, typically) used for items rendered with the default delegate. (QBrush)"
			return QVariant();	// No special foreground.
		case Qt::CheckStateRole:		// "[10] This role is used to obtain the checked state of an item. (Qt::CheckState)"
			return QVariant();	// Item not checkable.
		case Qt::InitialSortOrderRole:	// "[14] This role is used to obtain the initial sort order of a header view section. (Qt::SortOrder). This role was introduced in Qt 4.8"
			return QVariant();	// Use default sort order.

		// Accessibility roles:
		case Qt::AccessibleTextRole:		// "[11] The text to be used by accessibility extensions and plugins, such as screen readers. (QString)"
			return m_root.data().name();
//		case Qt::AccessibleDescriptionRole:	// "[12] A description of the item for accessibility purposes. (QString)"
//			return QVariant();	// No description.

		default:
			qDebug() << "Header item role (" << role << ") not supported yet.";
	}
	return QVariant();
}

Qt::ItemFlags ProjectModel::flags(const QModelIndex & index) const
{
	Q_UNUSED(index);

	// Flags according to Qt documentation:
	//	Qt::NoItemFlags				0	It does not have any properties set.
	//	Qt::ItemIsSelectable		1	It can be selected.
	//	Qt::ItemIsEditable			2	It can be edited.
	//	Qt::ItemIsDragEnabled		4	It can be dragged.
	//	Qt::ItemIsDropEnabled		8	It can be used as a drop target.
	//	Qt::ItemIsUserCheckable		16	It can be checked or unchecked by the user.
	//	Qt::ItemIsEnabled			32	The user can interact with the item.
	//	Qt::ItemIsTristate			64	The item can show three separate states. This enables automatic management of the state of parent items in QTreeWidget (checked if all children are checked, unchecked if all children are unchecked, or partially checked if only some children are checked).
	//	Qt::ItemNeverHasChildren	128	The item never has child items.
	//	Qt::ItemIsUserTristate		256	The user can cycle through three separate states. This value has been added in Qt 5.5.

	// Default implementation returns Qt::ItemIsSelectable | Qt::ItemIsEnabled.

	Qt::ItemFlags flags = Qt::ItemIsSelectable	| Qt::ItemIsEnabled;

	Node * node = static_cast<Node *>(index.internalPointer());
	if (node->isLeaf())
		flags |= Qt::ItemNeverHasChildren;

	return flags;
}

ProjectModel::iterator ProjectModel::begin()
{
	return iterator(& m_root);
}

ProjectModel::const_iterator ProjectModel::begin() const
{
	return const_iterator(& m_root);
}

ProjectModel::iterator ProjectModel::end()
{
	return iterator();
}

ProjectModel::const_iterator ProjectModel::end() const
{
	return const_iterator();
}

ProjectModel::Node & ProjectModel::root()
{
	return m_root;
}

QModelIndex ProjectModel::createIndex(int row, int column, Node * ptr) const
{
	return QAbstractItemModel::createIndex(row, column, ptr);
}

const ProjectModel::Node & ProjectModel::root() const
{
	return m_root;
}

}
}
