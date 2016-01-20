#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include "../platform.hpp"

#include <QAbstractItemModel>

namespace base {

/**
 * Project model.
 */
class CUTEHMI_API ProjectModel:
	public QAbstractItemModel
{
	public:
		explicit ProjectModel(QObject * parent = 0);

		// QAbstractItemModel read access, basic function.
		QModelIndex index(int row, int column, const QModelIndex & parent) const override;

		// QAbstractItemModel read access, basic function.
		QModelIndex parent(const QModelIndex & child) const override;

		// QAbstractItemModel read access, basic function.
		int rowCount(const QModelIndex & parent) const override;

		// QAbstractItemModel read access, basic function.
		int columnCount(const QModelIndex & parent) const override;

		// QAbstractItemModel read access, basic function.
		QVariant data(const QModelIndex & index, int role) const override;

		// QAbstractItemModel read access.
		QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

		// QAbstractItemModel read access.
		Qt::ItemFlags flags(const QModelIndex & index) const override;

		/**
		 * Temporary model setup.
		 *
		 * @todo remove this function when proper model loading function is implemented.
		 */
		void tmpSetup();

	protected:
		/**
		 * Project model node. Represents a node of tree-like structure.
		 */
		struct Node
		{
			friend class ProjectModel;

			public:
				/**
				 *	Node data.
				 */
				struct Data
				{
					friend class ProjectModel;
					friend class Node;

					public:
						/**
						 * Constructor.
						 * @param name name of the item. It will be used to display item in the view.
						 * @param object internal data object. Can be @p null. If provided, instance of this class will
						 * reset parent and take over ownership of object.
						 */
						explicit Data(const QString & name, QObject * object = nullptr);

						/**
						 * Set object.
						 * @param object internal object. Can be @p null. If provided, instance of this class will
						 * reset parent and take over ownership of object.
						 */
						void setObject(QObject * object);

						/**
						 * Get internal data object.
						 * @return internal data object or @p null.
						 */
						QObject * object() const;

						/**
						 * Get name.
						 * @return name.
						 */
						QString name() const;

					protected:
						/**
						 * Destructor. Non-virtual destructor protected to prevent blind subclassing.
						 */
						~Data();

					private:
						QString m_name;
						QObject * m_object;
				};

				typedef QList<Node *> ChildrenContainer;

				/**
				 * Constructor.
				 * @param data node data.
				 */
				explicit Node(const Data & data);

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
				 * @return parent node. For root node @p null is returned.
				 */
				const Node * parent() const;

				/**
				 * Get parent of this node.
				 * @return parent node. For root node @p null is returned.
				 */
				Node * parent();

				/**
				 * Add child node.
				 * @param child child node. Must not be @p null. Instance of this class will take over ownership
				 * of object.
				 */
				void addChild(Node * child);

				/**
				 * Get child at specified index (const version).
				 * @param index child index.
				 * @return child at specified index or @p null if child does not exist.
				 */
				const Node * child(int index) const;

				/**
				 * Get child at specified index.
				 * @param index child index.
				 * @return child at specified index or @p null if child does not exist.
				 */
				Node * child(int index);

				/**
				 * Get child index.
				 * @param child node to get index for.
				 * @return child node index or @p -1 if child was not found.
				 */
				int childIndex(Node * const & child) const;

				/**
				 * Count children.
				 * @return number of children.
				 */
				int countChildren() const;

			protected:
				/**
				 * Set parent.
				 * @param parent parent node. Must not be @p null as only root node can have @p null parent.
				 */
				void setParent(Node * parent);

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
				~Node();

			private:
				void allocateChildren();

				Data m_data;
				Node * m_parent;
				ChildrenContainer * m_children;	///< Children nodes. It's more safe to access this member via children() function.
		};

	private:
		Node m_root;
};

}

#endif // PROJECTMODEL_H
