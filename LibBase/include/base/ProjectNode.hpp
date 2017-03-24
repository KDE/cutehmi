#ifndef CUTEHMI_LIBBASE_INCLUDE_BASE_PROJECTNODE_HPP
#define CUTEHMI_LIBBASE_INCLUDE_BASE_PROJECTNODE_HPP

#include "internal/common.hpp"
#include "DataBlock.hpp"

#include <utils/NonCopyable.hpp>

#include <QStringList>

#include <iterator>
#include <memory>

namespace cutehmi {
namespace base {

/**
 * Project model node. Represents a node of tree-like structure of project. Objects of this class can not be instantiated directly.
 * It is only possible to add nodes to existing ProjectModel using addChild() function.
 *
 * Nodes serve several purposes. They reflect dependencies of the project, control lifetime of injected data and serve as extension
 * points, allowing various parts of application to communicate with each other. Each node has an id by which it may be referred.
 *
 * <principle id="cutehmi.base.ProjectNode.determined_destruction_order">
 * Destruction order of exposed data members is determined. The order is as follows:
 *		- child nodes (children()) in reverse order as they were added. Each child follows the order.
 *		- extensions.
 *		- node data (data()).
 *		.
 * </principle>
 */
class CUTEHMI_BASE_API ProjectNode:
	public utils::NonCopyable
{
	Q_GADGET

	friend class ProjectModel;
	friend class ProjectNodeTest;

	public:
		/**
		 *	Node data.
		 */
		struct CUTEHMI_BASE_API Data final:
			public DataBlock
		{
			/**
			 * Constructor.
			 * @param name name of the item. It will be used to display item in the view.
			 */
			explicit Data(const QString & name);

			Data(Data && other) = default;

			Data & operator =(Data && other) = default;

			/**
			 * Get name.
			 * @return name.
			 */
			QString name() const;

			/**
			 * Set name.
			 * @param name node name.
			 */
			void setName(const QString & name);

			private:
				QString m_name;
				//QIcon m_icon;
		};

		typedef QList<ProjectNode *> ChildrenContainer;
		typedef QHash<QString, QObject *> ExtensionsContainer;

		/**
		 * Access extension.
		 * @param extensionId extension id.
		 * @return extension object or @p nullptr if no extension was found for the given extension id.
		 *
		 * @internal non-const method, because extension object can technically keep reference to the Node object and modify it.
		 */
		Q_INVOKABLE QObject * extension(const QString & extensionId);

		/**
		 * Add extension.
		 * @param extensionId extension id. Given id can be used later to access extension object via extension() function.
		 * Id should be unique within the node.
		 * @param extension extension object.
		 *
		 * @note extension object won't be owned by Node.
		 */
		void addExtension(const QString & extensionId, QObject * extension);

		/**
		 * Add extension. Convenient function, which will use class name obtained from QObject meta-data as an extension id.
		 * Class name is obtained by QMetaObject::className() function and contains fully qualified name (with namespace).
		 * @param extension extension object. Same object should not be used for the second call of this function for the
		 * particular node.
		 *
		 * @note with this method only one instance of particular class can be added to the node. To add more objects of the
		 * same class one may use addExtension(const QString & extensionId, QObject * extension) variant. Consider however,
		 * adding child nodes instead.
		 *
		 * @note extension object won't be owned by Node.
		 */
		void addExtension(QObject * extension);

		/**
		 * Get list of extension ids.
		 * @return list of extension ids.
		 */
		QStringList extensionIds() const;

		/**
		 * Access node data (const version).
		 * @return node data.
		 */
		const Data & data() const;

		/**
		 * Access node data.
		 * @return node data.
		 */
		Data & data();

		/**
		 * Get parent of this node (const version).
		 * @return parent node. For root node @p nullptr is returned.
		 */
		const ProjectNode * parent() const;

		/**
		 * Get parent of this node.
		 * @return parent node. For root node @p nullptr is returned.
		 */
		ProjectNode * parent();

		/**
		 * Get root node (const version).
		 * @return root node.
		 */
		const ProjectNode * root() const;

		/**
		 * Get root node. Convenient function that walks up parents hierarchy up to root node.
		 * @return root node.
		 */
		ProjectNode * root();

		/**
		 * Get node id.
		 * @return node id.
		 */
		QString id() const;

		/**
		 * Add child node.
		 * @param id node id. Node id must be unique with respect to its siblings. Nodes, which have different parents may have the same id.
		 * Results of using the same id for nodes, which are children of the same parent, are undefined.
		 * @param data node data.
		 * @param leaf indicates if child node is a leaf. Leaf is a node that do not have
		 * any children.
		 * @return pointer to newly created child. Child is owned by instance of this class.
		 */
		ProjectNode * addChild(const QString & id, Data && data, bool leaf = true);

		/**
		 * Add child node. This version is provided for convenience. Random node id is generated automatically.
		 * @param data node data.
		 * @param leaf indicates if child node is a leaf. Leaf is a node that do not have
		 * any children.
		 * @return pointer to newly created child. Child is owned by instance of this class.
		 */
		ProjectNode * addChild(Data && data, bool leaf = true);

		/**
		 * Get child at specified index (const version).
		 * @param index child index.
		 * @return child at specified index or @p nullptr if child does not exist.
		 */
		const ProjectNode * child(int index) const;

		/**
		 * Get child at specified index.
		 * @param index child index.
		 * @return child at specified index or @p nullptr if child does not exist.
		 */
		ProjectNode * child(int index);

		/**
		 * Get child by specified id (const version).
		 * @param id id of the child.
		 * @return child identified by specified @a id or @p nullptr if child with specified @a id does not exist.
		 *
		 * @note this function searches all children for the specified @a id. For frequent access use child(int index) variant.
		 */
		const ProjectNode * child(const QString & id) const;

		/**
		 * Get child by specified id.
		 * @param id id of the child.
		 * @return child identified by specified @a id or @p nullptr if child with specified @a id does not exist.
		 *
		 * @note this function searches all children for the specified @a id. For frequent access use child(int index) variant.
		 */
		ProjectNode * child(const QString & id);

		/**
		 * Get child index.
		 * @param child node to get index for.
		 * @return child node index or @p -1 if child was not found.
		 */
		int childIndex(const ProjectNode * child) const;

		/**
		 * Get list of child ids.
		 * @return list of child ids.
		 *
		 * @note this function iterates over all children to produce the list, thus it should not be used frequently.
		 */
		QStringList childIds() const;

		/**
		 * Count children.
		 * @return number of children.
		 */
		int countChildren() const;

	protected:
		/**
		 * Constructor.
		 * @param data node data.
		 * @param id node id.
		 * @param children children container. Setting this to @p nullptr indicates that node is a leaf.
		 */
		ProjectNode(const QString & id, Data && data, std::unique_ptr<ChildrenContainer> children = nullptr);

		/**
		 * Get node index.
		 * @return node index with respect to parent's children container.
		 */
		int index() const;

		/**
		 * Set parent.
		 * @param parent parent node. Must not be @p nullptr as only root node can have @p nullptr parent.
		 * @param index node index with respect to parent's children container.
		 */
		void setParent(ProjectNode * parent, int index);

		/**
		 * Check whether node is a leaf. If node is a leaf it does not have capability to store children.
		 * Each node is initally a leaf to avoid unnecessary allocation of children container.
		 * @return @p true if node is a leaf, @p false otherwise.
		 *
		 * @note this function is focused on capability to store children. It may return @p true even
		 * if node does not have any child.
		 */
		bool isLeaf() const;

		/**
		 * Get extensions (const version). If container had not existed it will be created on the first
		 * call of this function.
		 * @return extensions container.
		 */
		const ExtensionsContainer * extensions() const;

		/**
		 * Get extensions. If container had not existed it will be created on the first call of this function.
		 * @return exetensions container.
		 */
		ExtensionsContainer * extensions();

		/**
		 * Get children (const version). If node was a leaf it becomes a node capable to store children
		 * after calling this function.
		 * @return children container.
		 */
		const ChildrenContainer * children() const;

		/**
		 * Get children. If node was a leaf it becomes a node capable to store children after calling this
		 * function.
		 * @return children container.
		 */
		ChildrenContainer * children();

		/**
		 * Destructor. Non-virtual destructor protected to prevent blind subclassing.
		 */
		~ProjectNode();

	private:
		struct Members
		{
			//<principle_ref id="cutehmi.base.ProjectNode.determined_destruction_order">
			ProjectNode * parent;
			int index;	///< Index with respect to parent's children container. Solely for optimization purposes.
			QString id;
			Data data;
			std::unique_ptr<ExtensionsContainer> extensions; ///< Extensions. It's more safe to access this member via extensions() function.
			std::unique_ptr<ChildrenContainer> children;	///< Children nodes. It's more safe to access this member via children() function.
			//</principle_ref>
		};

		void allocateExtensions();

		void allocateChildren();

		std::unique_ptr<Members> m;
};

}
}

#endif
