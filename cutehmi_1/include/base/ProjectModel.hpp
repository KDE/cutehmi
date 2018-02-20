#ifndef CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_PROJECTMODEL_HPP
#define CUTEHMI_CUTEHMI__BASE__1__LIB_INCLUDE_BASE_PROJECTMODEL_HPP

#include "internal/common.hpp"
#include "ProjectNode.hpp"

#include <QAbstractItemModel>

#include <iterator>
#include <memory>

namespace cutehmi {
namespace base {

/**
 * Project model. Project model is technically a tree, which uses ProjectNode instances as underlying data structure for its nodes.
 * Various aspects of the model are exposed as QAbstractItemModel, so that it can be used with standard Qt views.
 *
 * @principles
 *
 * <principle id="cutehmi.base.ProjectModel.internalPoiner">
 * For all valid items in the model, QModelIndex::internalPointer() is always associated with pointer
 * to object of type @p ProjectModel::Node, so that neither @p nullptr nor a pointer to any other object
 * type can be returned.
 * </principle>
 *
 * @endprinciples
 */
class CUTEHMI_BASE_API ProjectModel:
	public QAbstractItemModel
{
	Q_OBJECT

	template <typename NODE>
	struct Iterator;

	public:
		typedef Iterator<ProjectNode> iterator;
		typedef Iterator<const ProjectNode> const_iterator;

		Q_PROPERTY(const cutehmi::base::ProjectNode * root READ rootPtr CONSTANT)

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

		iterator begin();

		const_iterator begin() const;

		iterator end();

		const_iterator end() const;

		/**
		 * Get root node (const version).
		 * @return root node.
		 */
		const ProjectNode & root() const;

		/**
		 * Get root node.
		 * @return root node.
		 */
		ProjectNode & root();

	protected:
		// QAbstractItemModel
		QModelIndex createIndex(int row, int column, ProjectNode * ptr) const;	// shadow

		/**
		 * Root node pointer. This function is provided to deal with property system, which can not use references to non-copyable objects.
		 * @return root node pointer.
		 */
		const ProjectNode * rootPtr() const;

	private:
		template <typename NODE>
		struct Iterator :
			public std::iterator<std::forward_iterator_tag, NODE, std::ptrdiff_t>
		{
			typedef std::iterator<std::forward_iterator_tag, NODE, std::ptrdiff_t> Parent;

			typedef typename Parent::value_type value_type;
			typedef typename Parent::reference reference;
			typedef typename Parent::difference_type difference_type;
			typedef typename Parent::pointer pointer;
			typedef typename Parent::iterator_category iterator_category;

			// std::forward_iterator_tag
			Iterator();

			/**
			 * Constructor.
			 * @param node node.
			 */
			Iterator(NODE * node);

			// std::forward_iterator_tag
			reference operator *() const;

			// std::forward_iterator_tag
			pointer operator ->() const;

			// std::forward_iterator_tag
			Iterator & operator ++();

			// std::forward_iterator_tag
			Iterator operator ++(int);

			// std::forward_iterator_tag
			bool operator ==(const Iterator & other) const;

			// std::forward_iterator_tag
			bool operator !=(const Iterator & other) const;

			private:
				/**
				 * Get next sibling.
				 * @param node node, sibling of which should be returned.
				 * @param parent parent of @a node.
				 * @return sibling of @a node or @p nullptr if there is no child next to @a node.
				 */
				NODE * nextSibling(NODE * node, NODE * parent) const;

				NODE * m_me;
		};

		struct Members
		{
			ProjectNode root;

			Members();
		};

		utils::MPtr<Members> m;
};

template <typename NODE>
ProjectModel::Iterator<NODE>::Iterator():
	m_me(nullptr)
{
}

template <typename NODE>
ProjectModel::Iterator<NODE>::Iterator(NODE * node):
	m_me(node)
{
}

template <typename NODE>
typename ProjectModel::Iterator<NODE>::reference ProjectModel::Iterator<NODE>::operator *() const
{
	Q_ASSERT(m_me != nullptr);

	return *m_me;
}

template <typename NODE>
typename ProjectModel::Iterator<NODE>::pointer ProjectModel::Iterator<NODE>::operator ->() const
{
	Q_ASSERT(m_me != nullptr);

	return m_me;
}

template <typename NODE>
ProjectModel::Iterator<NODE> & ProjectModel::Iterator<NODE>::operator ++()
{
	Q_ASSERT(m_me != nullptr);

	if (m_me->countChildren() != 0)
		m_me = *(m_me->children()->begin());
	else if (m_me->parent() != nullptr) {
		NODE * sibling;
		while ((sibling = nextSibling(m_me, m_me->parent())) == nullptr) {
			m_me = m_me->parent();
			if (m_me->parent() == nullptr) {
				// Root node reached.
				m_me = nullptr;
				return *this;
			}
		}
		m_me = sibling;
	} else
		m_me = nullptr;
	return *this;
}

template <typename NODE>
ProjectModel::Iterator<NODE> ProjectModel::Iterator<NODE>::operator ++(int)
{
	Iterator<NODE> copy(*this);
	++(*this);
	return copy;
}

template <typename NODE>
bool ProjectModel::Iterator<NODE>::operator ==(const Iterator & other) const
{
	return other.m_me == m_me;
}

template <typename NODE>
bool ProjectModel::Iterator<NODE>::operator !=(const Iterator & other) const
{
	return other.m_me != m_me;
}

template <typename NODE>
NODE * ProjectModel::Iterator<NODE>::nextSibling(NODE * node, NODE * parent) const
{
	return parent->child(parent->childIndex(node) + 1);
}

}
}

#endif

//(c)MP: Copyright © 2017, Michal Policht. All rights reserved.
//(c)MP: This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
